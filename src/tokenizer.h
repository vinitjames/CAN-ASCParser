#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <memory>
#include <string>
#include <vector>

#include "token.h"

class Tokenizer {
 public:
  Tokenizer() = delete;
  Tokenizer(const std::string& str);
  Token& getCurrToken();
  Token& getNextToken();
  Token& getPrevToken();
  const Token& getCurrToken() const;
  const Token& getNextToken() const;
  const Token& getPrevToken() const;
  void resetTokenStream() const;
  Token& front();
  Token& back();
  const Token& front() const;
  const Token& back() const;
  std::size_t size() const;
  Token& operator[](const std::size_t index);
  const Token& operator[](const std::size_t index) const;

  // add [] operator and front and back and length

 private:
  void _tokenizeStream(const std::string& str);
  std::vector<Token> _token_stream;
  mutable std::size_t _index = 0;
};

#endif /* TOKENIZER_H */
