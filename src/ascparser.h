#include <fstream>
#include <string>
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

	bool getMessasge();
	Message& ParseCANFD(const std::string& line);
private:
	bool parseHeader();
	bool checkHeader();
	
	std::ifstream _ifs;
	std::string _date;
	std::string _base;
	std::string _timestamp_format;
	bool _internal_events_logged = false;
};
