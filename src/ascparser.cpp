#include "ascparser.h"

#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "ascparser.h"
#include "message.h"

ASCParser::ASCParser(const std::string& filename) {
  if (filename.substr(filename.find(".asc")) != ".asc")
    throw std::invalid_argument("filename is not of .asc type");
  _ifs.open(filename, std::ifstream::in);
  if (!_ifs.is_open()) throw std::invalid_argument("Could not open filename");
  if (!parseHeader()) throw std::domain_error("asc file with wrong header");
}

bool ASCParser::parseHeader() {
  std::string word;
  while (_ifs >> word) {
    if (word == "date") {
      std::getline(_ifs, _date);
      continue;
    }

    if (word == "base") {
      _ifs >> _base;
      continue;
    }

    if (word == "timestamps") {
      _ifs >> _timestamp_format;
      continue;
    }

    if (word == "internal") {
      _internal_events_logged = true;
      break;
    }

    if (word == "no") {
      _internal_events_logged = false;
      break;
    }

    return false;
  }

  return checkHeader();
}

std::unique_ptr<Message> ASCParser::getMessage() {
  std::string line;
  if (!std::getline(_ifs, line)) {
    eof_reached = true;
    return std::make_unique<Message>();
  }

  std::vector<std::string> split_frame = splitFrame(line);

  if (!checkTimestamp(split_frame)) return nullptr;

  if (isCANFD(split_frame)) {
    return std::make_unique<Message>(parseCANFD(split_frame));
  }

  if (isCAN(split_frame))
    return std::make_unique<Message>(parseCAN(split_frame));
  return nullptr;
}

bool ASCParser::checkTimestamp(const std::vector<std::string>& split_frame) {
  return isDouble(split_frame[0]);
}

bool ASCParser::isCAN(const std::vector<std::string>& split_frame) {
  if (isInt(split_frame[1]))
    return (split_frame[2] != "Statistic:") && (split_frame[2] != "J1939TP");
  return false;
}

bool ASCParser::isInt(const std::string& str) {
  char* endptr = nullptr;
  std::strtol(str.c_str(), &endptr, 10);
  return *endptr == '\0';
}

bool ASCParser::isDouble(const std::string& str) {
  char* endptr = nullptr;
  std::strtod(str.c_str(), &endptr);
  return *endptr == '\0';
}

bool ASCParser::isCANFD(const std::vector<std::string>& split_frame) {
  return split_frame[1] == "CANFD";
}

std::vector<std::string> ASCParser::splitFrame(const std::string& frame) {
  std::istringstream ss(frame);
  std::vector<std::string> splitframe(std::istream_iterator<std::string>{ss},
                                      std::istream_iterator<std::string>());
  return splitframe;
}

Message ASCParser::parseCANFD(const std::vector<std::string>& split_frame) {
  Message msg;
  msg.timestamp(std::stod(split_frame[0]));
  msg.is_fd(true);
  size_t _index = 2;
  msg.channel(std::stoi(split_frame[_index++]) - 1);
  msg.is_rx(split_frame[_index++] == "Rx");
  if (split_frame[_index] == "ErrorFrame") {
    msg.is_error_frame(true);
    return msg;
  }

  msg.arbitration_id(getArbitrationID(split_frame[_index++]));

  if (!isInt(split_frame[_index])) {
    _index++;
  }

  msg.bit_rate_switch(split_frame[_index++] == "1");
  msg.error_state_indicator(split_frame[_index++] == "1");
  msg.dlc(std::stoi(split_frame[_index++], nullptr, getBase()));
  int _data_length = std::stoi(split_frame[_index++]);
  if (_data_length == 0) {
    msg.is_remote_frame(true);
    return msg;
  }
  msg._data = parseDataFromString(split_frame, _data_length, _index);
  return msg;
}

Message ASCParser::parseCAN(const std::vector<std::string>& split_frame) {
  Message msg;
  msg.timestamp(std::stod(split_frame[0]));
  msg.is_fd(false);
  size_t _index = 1;
  msg.channel(std::stoi(split_frame[_index++]) - 1);
  if (split_frame[_index] == "ErrorFrame") {
    msg.is_error_frame(true);
    return msg;
  }

  msg.arbitration_id(getArbitrationID(split_frame[_index++]));
  msg.is_rx(split_frame[_index++] == "Rx");
  msg.is_remote_frame(split_frame[_index] == "r");
  if (msg.is_remote_frame()) {
    msg.dlc(parseCANRemote(split_frame, _index + 1));
    return msg;
  }
  if (split_frame[_index++] != "d") return msg;
  msg.dlc(std::stoi(split_frame[_index++], nullptr, getBase()));
  if (split_frame.size() <= _index) return msg;

  msg._data = parseDataFromString(split_frame, msg.dlc(), _index);
  return msg;
}

int ASCParser::parseCANRemote(const std::vector<std::string>& split_frame,
                              const unsigned int index) {
  if (split_frame.size() <= index) return 0;
  std::string nextToken{split_frame[index]};
  if (!isInt(nextToken)) return 0;
  return std::stoi(nextToken);
}

int ASCParser::getArbitrationID(const std::string& can_id_str) {
  if (can_id_str.back() == 'x')
    return std::stoi(can_id_str.substr(0, can_id_str.length() - 1), nullptr,
                     getBase());
  return std::stoi(can_id_str, nullptr, getBase());
}

std::vector<uint8_t> ASCParser::parseDataFromString(
    const std::vector<std::string>& split_frame, size_t length, size_t index) {
  std::vector<uint8_t> data;
  for (int i = 0; i < length; i++)
    data.push_back(std::stoi(split_frame[index++], nullptr, getBase()));
  return data;
}

bool ASCParser::checkHeader() {
  if ((_base != "hex") && (_base != "dec")) return false;
  if (_date.empty()) return false;
  if ((_timestamp_format != "absolute") && (_timestamp_format != "relative"))
    return false;
  return true;
}

int ASCParser::getBase() { return _base == "hex" ? 16 : 10; }

ASCParser::~ASCParser() noexcept { _ifs.close(); }
