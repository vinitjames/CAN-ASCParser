#include <iostream>

#include "../src/tokenizer.h"
int main(int argc, char *argv[]) {
  Tokenizer tokenizer("0.23 18EBFF00x");

  std::cout << tokenizer.front().getDoubleValue() << std::endl;
  std::cout << tokenizer.back().getHexValue() << std::endl;

  std::cout << (tokenizer.front() == 0.2) << std::endl;
  std::cout << (tokenizer.front() == 0.234) << std::endl;
  std::cout << (tokenizer.back() == "18EBFF00x") << std::endl;
  std::cout << (tokenizer.front() == Type::INT) << std::endl;
  std::cout << (tokenizer.front() == Type::DOUBLE) << std::endl;
  std::cout << (tokenizer.back() == Type::INT) << std::endl;
  std::cout << (tokenizer.back() == Type::DOUBLE) << std::endl;
  std::cout << tokenizer.back().getIntValue() << std::endl;
  return 0;
}
