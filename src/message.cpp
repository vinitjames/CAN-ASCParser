#include "message.h"

void  Message::arbiration_id(int id){ _arbitration_id = id;}
int Message::arbitration_id() const {return _arbitration_id;}

void Message::bit_rate_switch(bool bit_rate_switch) {  _bit_rate_switch = bit_rate_switch;};
bool Message::bit_rate_switch() const { return _bit_rate_switch;}
	
void Message::channel(int channel){_channel = channel;}
int Message::channel() const {return _channel;}

void Message::dlc(int dlc){ _dlc = dlc;}
int Message::dlc() const {return _dlc;}

void Message::is_error_frame(bool err_state_ind) { _error_state_indicator = err_state_ind;}
bool Message::is_error_frame() const { return _error_state_indicator;}

void Message::is_extended(bool is_extended){ _is_extended_id = is_extended;}
bool Message::is_extended() const { return _is_extended_id;}
	
void Message::is_fd(bool is_fd) {_is_fd = is_fd;}
bool Message::is_fd() const {return _is_fd;}

void Message::is_remote_frame(bool is_remote_frame){_is_remote_frame = is_remote_frame;}
bool Message::is_remote_frame() const {return _is_remote_frame;}
	
void Message::is_rx(bool is_fd) {_is_fd = is_fd;}
bool Message::is_rx() const {return _is_fd;};

void Message::timestamp(double timestamp){ _timestamp = timestamp;}
double Message::timestamp() const {return _timestamp;}

const std::vector<uint8_t>& data();
