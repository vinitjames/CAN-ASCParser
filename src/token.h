#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class Type { STRING, INT, DOUBLE, HEX, NONE };

class Token {
 public:
  Token() = delete;
  Token(const std::string& val);
  virtual ~Token() = default;
  bool operator==(const Token& other) const;
  bool operator==(const Type& type) const;
  bool operator==(const std::string& str_val) const;
  bool operator==(const int& val) const;
  bool operator==(const double& val) const;
  bool operator!=(const Token& other) const;
  bool operator!=(const Type& type) const;
  bool operator!=(const std::string& other) const;
  bool operator!=(const int& val) const;
  bool operator!=(const double& val) const;

  const Type& getType() const;
  const std::string& getStringValue() const;
  int getIntValue() const;
  double getDoubleValue() const;
  int getHexValue() const;

 private:
  void _setBaseValueType() const;
  mutable Type _type = Type::NONE;
  std::string _str_val;
  mutable int _int_val = 0;
  mutable double _doub_val = 0;
};

#endif /* TOKEN_H */
