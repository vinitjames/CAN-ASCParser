#include "ascparser.h"
#include <exception>
#include <iterator>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include "message.h"
#include "tokenizer.h"
#include <iostream>

ASCParser::ASCParser(const std::string& filename)
	:_filename{filename}{
	if (filename.substr(filename.find(".asc")) != ".asc")
		throw std::invalid_argument("filename is not of .asc type");
  
	_ifs.open(filename, std::ifstream::in);
	if (!_ifs.is_open()) throw std::invalid_argument("Could not open filename");
	if (!parseHeader()) throw std::domain_error("asc file with wrong header");
}

void ASCParser::reinit(){
	if(_ifs.is_open())
		_ifs.close();
	_ifs.open(_filename, std::ifstream::in);	
	parseHeader();
	_eof_reached = false;
}

bool ASCParser::parseHeader() {
	std::string word; 
  while (_ifs >> word){
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
  std::unique_ptr<Message> msg = nullptr;
  
  while (!msg && loadNextStream()) {     
    Tokenizer tokenized_frame(_currStream);
    try {
		if (!checkTimestamp(tokenized_frame)) {
			continue;
		}

      if (isCANFD(tokenized_frame))
        msg = std::make_unique<Message>(parseCANFD(tokenized_frame));

      if (isCAN(tokenized_frame))
        msg = std::make_unique<Message>(parseCAN(tokenized_frame));
	  
    }

    catch (std::exception& e) {
		continue;
    }
  }
  return msg;
}

bool ASCParser::loadNextStream(){
	 if (!std::getline(_ifs, _currStream)) {
      _eof_reached = true;
    }
	 return !_eof_reached;
}


bool ASCParser::checkTimestamp(const Tokenizer& tokenized_frame) {
  return tokenized_frame.front() == Type::DOUBLE;
}

bool ASCParser::isCAN(const Tokenizer& tokenized_stream) {
  if (tokenized_stream[1] == Type::INT)
    return (tokenized_stream[2] != "Statistic:") &&
           (tokenized_stream[2] != "J1939TP");
  return false;
}

bool ASCParser::isCANFD(const Tokenizer& tokenizer) {
  return tokenizer[1] == "CANFD";
}

Message ASCParser::parseCANFD(const Tokenizer& tokenized_frame) {
  tokenized_frame.resetTokenStream();
  Message msg;
  msg.timestamp(tokenized_frame.getCurrToken().getDoubleValue());
  msg.is_fd(tokenized_frame.getNextToken() == "CANFD");

  msg.channel(tokenized_frame.getNextToken().getIntValue() - 1);
  msg.is_rx(tokenized_frame.getNextToken() == "Rx");
  if (tokenized_frame.getNextToken() == "ErrorFrame") {
    msg.is_error_frame(true);
    return msg;
  }

  msg.arbitration_id(getArbitrationID(tokenized_frame.getCurrToken()));

  if (tokenized_frame.getNextToken() == Type::INT)
    msg.bit_rate_switch(tokenized_frame.getCurrToken() == "1");
  else
    msg.bit_rate_switch(tokenized_frame.getNextToken() == "1");

  msg.error_state_indicator(tokenized_frame.getNextToken() == "1");

  if (getBase() == 16)
    msg.dlc(tokenized_frame.getNextToken().getHexValue());
  else
    msg.dlc(tokenized_frame.getNextToken().getIntValue());

  int _data_length = tokenized_frame.getNextToken().getIntValue();
  if (_data_length == 0) {
    msg.is_remote_frame(true);
    return msg;
  }
  msg.data(parseDataFromString(tokenized_frame, _data_length));
  return msg;
}

Message ASCParser::parseCAN(const Tokenizer& tokenized_frame) {
  tokenized_frame.resetTokenStream();
  Message msg;
  msg.timestamp(tokenized_frame.getCurrToken().getDoubleValue());
  msg.is_fd(false);
  msg.channel(tokenized_frame.getNextToken().getIntValue() - 1);
  if (tokenized_frame.getNextToken() == "ErrorFrame") {
    msg.is_error_frame(true);
    return msg;
  }

  msg.arbitration_id(getArbitrationID(tokenized_frame.getCurrToken()));
  msg.is_rx(tokenized_frame.getNextToken() == "Rx");
  msg.is_remote_frame(tokenized_frame.getNextToken() == "r");
  if (msg.is_remote_frame()) {
    msg.dlc(parseCANRemote(tokenized_frame));
    return msg;
  }
  if (tokenized_frame.getCurrToken() != "d") return msg;
  if (getBase() == 16)
    msg.dlc(tokenized_frame.getNextToken().getHexValue());
  else
    msg.dlc(tokenized_frame.getNextToken().getIntValue());

  msg.data(parseDataFromString(tokenized_frame, msg.dlc()));
  return msg;
}

int ASCParser::parseCANRemote(const Tokenizer& tokenized_frame) {
  try {
    if (tokenized_frame.getNextToken() != Type::INT) return 0;
    return tokenized_frame.getCurrToken().getIntValue();
  } catch (std::exception& e) {
    return 0;
  }
}

int ASCParser::getArbitrationID(const Token& token) {
  if (getBase() == 16) return token.getHexValue();
  return token.getIntValue();
}

std::vector<uint8_t> ASCParser::parseDataFromString(
    const Tokenizer& tokenized_frame, std::size_t length) {
  std::vector<uint8_t> data;
  for (int i = 0; i < length; i++) {
    if (getBase() == 16)
      data.push_back(tokenized_frame.getNextToken().getHexValue());
    else
      data.push_back(tokenized_frame.getNextToken().getHexValue());
  }

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

bool ASCParser::fileEnded() { return _eof_reached;}

ASCParser::~ASCParser() noexcept { _ifs.close(); }

