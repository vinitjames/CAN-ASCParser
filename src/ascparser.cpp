#include "ascparser.h"
#include <stdexcept>
#include<iostream>
#include <sstream>
#include <iterator>

ASCParser::ASCParser(const std::string& filename){
	if(filename.substr(filename.find(".asc")) != ".asc")
		throw std::invalid_argument("filename is not of .asc type");
	_ifs.open(filename, std::ifstream::in);
	if(!_ifs.is_open())
		throw std::invalid_argument("Could not open filename");
	
	}


bool ASCParser::parseHeader(){
	std::string word;
	while(_ifs >> word){
		
		if(word == "date"){
			std::getline(_ifs, _date);
			continue;
		}
		
		if(word == "base"){
			_ifs >> _base;
			continue;
		}
		
		if(word == "timestamps"){
			_ifs >> _timestamp_format;
			continue;
		}
		
		if(word ==  "internal"){
			_internal_events_logged = true;
			break;
		}
		
		if(word == "no"){
			_internal_events_logged = false;
			break;
		}

		return false;
	}
	
	return checkHeader();
}

bool ASCParser::getMessasge(){
	std::string line;
	std::getline(_ifs,line);
	std::vector<std::string> split_frame = splitFrame(line);
	if(checkTimestamp(split_frame))
		return false;
	
	if (isCANFD(split_frame))
		return parseCANFD(line);
	else:
		return parseCAN(line);
	return false;
}

bool ASCParser::checkTimestamp(std::vector<std::string>& split_frame){
	char* endptr;
	double timestamp = strtod(split_frame[0].c_str(), &endptr);
	return *endptr == 0
}

bool ASCParser::isCANFD(std::vector<std::string>& split_frame){
	return split_frame[1] == "CANFD";
	
}

std::vector<std::string>splitFrame(const std::string& frame){
	std::istringstream ss(frame);
	std::vector<std::string> splitframe(std::istream_iterator<std::string>{ss},
										std::istream_iterator<std::string>());
	
}

Message ParseCANFD(const std::vector<std::string>& split_frame){
	Message msg;
	size_t _index = 2;
	msg.is_fd(true);
	msg.channel(stoi(split_frame[_index++].c_str()) - 1);
	msg.is_rx(split_frame[_index++] == "Rx");
	if(split_frame[_index] == "errorframe"){
		msg.is_error_frame(true);
		return msg;		
	}
	msg.arbitration_id(get_arbitraionid(split_frame[_index++]));

	if(!stoi(split_frame[_index].c_str())){
		_index++;
		}
	
	msg.bit_rate_switch(split_frame[_index++] == "1");
	msg.error_state_indicator(split_frame[_index++] == "1");
	msg.dlc(stoi(split_frame[_index++], 16));
	msg.data_length(stoi(split_frame[_index++]));
	if(msg.data_length() == 0){
		msg.is_remote_frame(true);
		return msg;
	}

	msg.data = ParseDataFromString(split_frame, msg.data_length(), _index);

	return msg;			
}

Message ParseCAN(const std::vector<std::string>& split_frame){
	Message msg;
	size_t _index = 1;
	msg.is_fd(false);
	msg.channel(std::stoi(split_frame[_index++].c_str()) - 1);
	if(split_frame[_index] == "errorframe"){
		msg.is_error_frame(true);
		return msg;		
	}
	
	msg.arbitration_id(get_arbitraionid(split_frame[_index++]));
	msg.is_rx(split_frame[_index++] == "Rx");
	if(!std::stoi(split_frame[_index].c_str())){
		_index++;
		}
	
	msg.bit_rate_switch(split_frame[_index++] == "1");
	msg.error_state_indicator(split_frame[_index++] == "1");
	msg.dlc(stoi(split_frame[_index++], 16));
	msg.data_length(stoi(split_frame[_index++]));
	if(msg.data_length() == 0){
		msg.is_remote_frame(true);
		return msg;
	}

	msg.data = ParseDataFromString(split_frame, msg.data_length(), _index);

	return msg;			
}


std::vector<uint8_t> ParseDataFromString(const std::vector<std::string>& split_frame,
										 size_t length, size_t index){
	std::vector<uint8_t> data(length);
	for(int i = 0; i<length; i++)
		data.push_back(stoi(split_frame[index++]));
	return data;
}

bool ASCParser::checkHeader(){
	if((_base != "hex")&&(_base != "dec"))
		return false;
	if(_date.empty())
		return false;
	if((_timestamp_format != "absolute")&&(_timestamp_format != "relative"))
		return false;
	return true;
}

ASCParser::~ASCParser()noexcept{
	_ifs.close();
}

int main(int argc, char *argv[])
{
    ASCParser parser("../testfile.asc");
	std::cout<<parser.parseHeader();
    return 0;
}
