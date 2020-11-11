#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace StringUtil{

	bool StringtoInt(const ::std::string& str, int* val);

	bool StringtoDouble(const ::std::string& str, double* val);

	bool StringtoHex(const ::std::string& str, int* val);
	
}

#endif /* UTILS_H */
