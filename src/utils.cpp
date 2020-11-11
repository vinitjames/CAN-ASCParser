#include "utils.h"

#include <cstdlib>

namespace StringUtil {

bool StringtoInt(const ::std::string& str, int* val) {
  char* endptr = nullptr;
  int _val;
  _val = ::std::strtol(str.c_str(), &endptr, 10);
  if (*endptr == '\0') {
    *val = _val;
    return true;
  }
  return false;
}

bool StringtoHex(const ::std::string& str, int* val) {
  char* endptr = nullptr;
  int _val;
  if (str.back() == 'x')
    _val = std::strtol(str.substr(0, str.length() - 1).c_str(), &endptr, 16);
  else
    _val = std::strtol(str.c_str(), &endptr, 16);
  if (*endptr == '\0') {
    *val = _val;
    return true;
  }
  return false;
}

bool StringtoDouble(const ::std::string& str, double* val) {
  char* endptr = nullptr;
  double _val;
  _val = ::std::strtod(str.c_str(), &endptr);
  if (*endptr == '\0') {
    *val = _val;
    return true;
  }
  return false;
}

}  // namespace StringUtil
