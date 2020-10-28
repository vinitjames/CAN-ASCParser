#ifndef ASCPARSER_H
#define ASCPARSER_H

#include <fstream>
#include <string>
#include <memory>
#include "message.h"

class ASCParser
{
public:
	//! Default constructor
	ASCParser(const std::string& filename) ;

	//! Copy constructor
	ASCParser(const ASCParser &other) {}

	//! Move constructor
	ASCParser(ASCParser &&other) noexcept{}

	//! Destructor
	virtual ~ASCParser() noexcept;

	//! Copy assignment operator
	ASCParser& operator=(const ASCParser &other);

	//! Move assignment operator
	ASCParser& operator=(ASCParser &&other) noexcept;

	std::unique_ptr<Message> getMessage();
	Message parseCANFD(const std::vector<std::string>& split_frame);
	Message parseCAN(const std::vector<std::string>& split_frame);
	bool fileEnded(){return eof_reached;}
private:
	bool parseHeader();
	bool checkHeader();
	int getArbitrationID(const std::string& can_id_str);
	int getBase();
	bool checkTimestamp(const std::vector<std::string>& split_frame);
	std::vector<std::string> splitFrame(const std::string& frame);
	bool isCANFD(const std::vector<std::string>& split_frame);
	bool isCAN(const std::vector<std::string>& split_frame);
	bool isInt(const std::string& str);
	bool isDouble(const std::string& str);
	std::vector<uint8_t> parseDataFromString(const std::vector<std::string>& split_frame,
											 size_t length, size_t index);
	std::ifstream _ifs;
	std::string _date;
	std::string _base;
	std::string _timestamp_format;
	bool _internal_events_logged = false;
	bool eof_reached = false;
};

#endif /* ASCPARSER_H */
