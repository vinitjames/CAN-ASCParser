#include "tokenizer.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

Tokenizer::Tokenizer(const std::string& str) {
  if (str.empty())
    throw std::invalid_argument("Tokenizer: Initialized with empty string");
  _tokenizeStream(str);
}

void Tokenizer::_tokenizeStream(const std::string& str) {
  std::istringstream ss(str);
  std::string token_str;
  while (ss >> token_str) _token_stream.push_back(Token(token_str));
}

Token& Tokenizer::operator[](const std::size_t index) {
  if ((index < 0) || (index >= _token_stream.size()))
    throw ::std::out_of_range("index out of range of stream");
  return _token_stream[index];
}

const Token& Tokenizer::operator[](const std::size_t index) const {
  if ((index < 0) || (index >= _token_stream.size()))
    throw ::std::out_of_range("index out of range of stream");
  return _token_stream[index];
}

Token& Tokenizer::front() { return _token_stream.front(); }

Token& Tokenizer::back() { return _token_stream.back(); }

const Token& Tokenizer::front() const { return _token_stream.front(); }

const Token& Tokenizer::back() const { return _token_stream.back(); }

std::size_t Tokenizer::size() const { return _token_stream.size(); }

Token& Tokenizer::getNextToken() {
  if (++_index >= _token_stream.size())
    throw std::out_of_range("The token stream ended can't get next value");
  return _token_stream[_index];
}

Token& Tokenizer::getCurrToken() { return _token_stream[_index]; }

Token& Tokenizer::getPrevToken() {
  if (_index == 0)
    throw std::out_of_range(
        "The token stream is in inital position. No previous value");
  return _token_stream[--_index];
}

const Token& Tokenizer::getNextToken() const {
  if (++_index >= _token_stream.size())
    throw std::out_of_range("The token stream ended can't get next value");
  return _token_stream[_index];
}

const Token& Tokenizer::getCurrToken() const { return _token_stream[_index]; }

const Token& Tokenizer::getPrevToken() const {
  if (_index == 0)
    throw std::out_of_range(
        "The token stream is inital position. No previous value");
  return _token_stream[--_index];
}

void Tokenizer::resetTokenStream() const { _index = 0; }
