#include "message.h"

Message::Message(Message&& other) noexcept
    : _timestamp{other._timestamp},
      _arbitration_id{other._arbitration_id},
      _is_extended_id{other._is_extended_id},
      _is_remote_frame{other._is_remote_frame},
      _is_error_frame{other._is_error_frame},
      _channel{other._channel},
      _dlc{other._dlc},
      _is_fd{other._is_fd},
      _is_rx{other._is_rx},
      _bit_rate_switch{other._bit_rate_switch},
      _error_state_indicator{other._error_state_indicator},
      _data{std::move(other._data)} {}

Message& Message::operator=(Message&& other) noexcept {
  if (this != &other) {
    _timestamp = other._timestamp;
    _arbitration_id = other._arbitration_id;
    _is_extended_id = other._is_extended_id;
    _is_remote_frame = other._is_remote_frame;
    _is_error_frame = other._is_error_frame;
    _channel = other._channel;
    _dlc = other._dlc;
    _is_fd = other._is_fd;
    _is_rx = other._is_rx;
    _bit_rate_switch = other._bit_rate_switch;
    _error_state_indicator = other._error_state_indicator;
    _data = std::move(other._data);
  }
  return *this;
}

void Message::arbitration_id(int id) { _arbitration_id = id; }
int Message::arbitration_id() const { return _arbitration_id; }

void Message::bit_rate_switch(bool bit_rate_switch) {
  _bit_rate_switch = bit_rate_switch;
};
bool Message::bit_rate_switch() const { return _bit_rate_switch; }

void Message::channel(int channel) { _channel = channel; }
int Message::channel() const { return _channel; }

void Message::dlc(int dlc) { _dlc = dlc; }
int Message::dlc() const { return _dlc; }

void Message::error_state_indicator(bool err_state_ind) {
  _error_state_indicator = err_state_ind;
}
bool Message::error_state_indicator() const { return _error_state_indicator; }

void Message::is_error_frame(bool is_error_frame) {
  _is_error_frame = is_error_frame;
}
bool Message::is_error_frame() const { return _is_error_frame; }

void Message::is_extended(bool is_extended) { _is_extended_id = is_extended; }
bool Message::is_extended() const { return _is_extended_id; }

void Message::is_fd(bool is_fd) { _is_fd = is_fd; }
bool Message::is_fd() const { return _is_fd; }

void Message::is_remote_frame(bool is_remote_frame) {
  _is_remote_frame = is_remote_frame;
}
bool Message::is_remote_frame() const { return _is_remote_frame; }

void Message::is_rx(bool is_rx) { _is_rx = is_rx; }
bool Message::is_rx() const { return _is_rx; };

void Message::timestamp(double timestamp) { _timestamp = timestamp; }
double Message::timestamp() const { return _timestamp; }

void Message::data(std::vector<uint8_t>&& data) { _data = std::move(data); }
const std::vector<uint8_t>& Message::data() const { return _data; }
