#include "token.h"

#include <stdexcept>

#include "utils.h"

Token::Token(const std::string& str_val) : _str_val{str_val} {}

bool Token::operator==(const Token& other) const {
  return (_type == other._type) && (_str_val == other._str_val);
}

bool Token::operator==(const std::string& str_val) const {
  return (_str_val == str_val);
}

bool Token::operator==(const Type& type) const {
  if (_type == Type::NONE) _setBaseValueType();
  return _type == type;
}

bool Token::operator==(const int& int_val) const {
  if (_type == Type::NONE) _setBaseValueType();
  return (_type == Type::INT) && (_int_val == int_val);
}

bool Token::operator==(const double& double_val) const {
  if (_type == Type::NONE) _setBaseValueType();
  return (_type == Type::DOUBLE) && (_doub_val == double_val);
}

bool Token::operator!=(const Token& other) const { return !(*this == other); }

bool Token::operator!=(const std::string& str_val) const {
  return !(*this == str_val);
}

bool Token::operator!=(const Type& type) const { return !(*this == type); }

bool Token::operator!=(const int& int_val) const { return !(*this == int_val); }

bool Token::operator!=(const double& double_val) const {
  return !(*this == double_val);
}

const Type& Token::getType() const {
  if (_type == Type::NONE) _setBaseValueType();
  return _type;
}

void Token::_setBaseValueType() const {
  if (StringUtil::StringtoInt(_str_val, &_int_val))
    _type = Type::INT;

  else if (StringUtil::StringtoDouble(_str_val, &_doub_val))
    _type = Type::DOUBLE;

  else
    _type = Type::STRING;
}

int Token::getIntValue() const {
  if (_type == Type::NONE) _setBaseValueType();
  if (_type != Type::INT)
    throw std::invalid_argument("Current Token is not of type Int.");
  return _int_val;
}

double Token::getDoubleValue() const {
  if (_type == Type::NONE) _setBaseValueType();
  if (_type != Type::DOUBLE)
    throw std::invalid_argument("Current Token is not of type Int.");
  return _doub_val;
}

int Token::getHexValue() const {
  if (_type == Type::NONE) _setBaseValueType();
  if (_type == Type::DOUBLE)
    throw std::invalid_argument("Cannot convert double to hex");
  int val;
  if (!StringUtil::StringtoHex(_str_val, &val))
    throw std::invalid_argument("Cannot convert token to hex ");
  return val;
}

const std::string& Token::getStringValue() const { return _str_val; }
