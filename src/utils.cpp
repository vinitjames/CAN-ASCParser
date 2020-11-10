#include <cstdlib>
#include "utils.h"

namespace StringUtil{

	bool StringtoInt(const ::std::string& str, int* val){
		char* endptr = nullptr;
		*val = ::std::strtol(str.c_str(), &endptr, 10);
		return *endptr == '\0';
	}

	bool StringtoHex(const ::std::string& str, int* val){
		char* endptr = nullptr;
		if (str.back() == 'x')
			*val = std::strtol(str.substr(0, str.length() - 1).c_str(), &endptr, 16);
		*val = std::strtol(str.c_str(), &endptr, 16);
		return *endptr == '\0';
	}

	bool StringtoDouble(const ::std::string& str, double* val) {
		char* endptr = nullptr;
		*val = ::std::strtod(str.c_str(), &endptr);
		return *endptr == '\0';
	}

	
}
