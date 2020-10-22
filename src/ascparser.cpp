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
	
	
		
	if (is_canfd_frame(line))
		return parseCANFD(line);
	if(is_can_frame(line))
		return parseCAN(line);
	return false;
}

bool ASCParser::checkTimestamp(std::vector<std::string>& split_frame){
	char* endptr;
	double timestamp = strtod(split_frame[0].c_str(), &endptr);
	return *endptr == 0
}

std::vector<std::string>splitFrame(const std::string& frame){
	std::istringstream ss(frame);
	std::vector<std::string> splitframe(std::istream_iterator<std::string>{ss},
										std::istream_iterator<std::string>());
	
}

Message& ParseCANFD(const std::string& line){
	line.substr()
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
