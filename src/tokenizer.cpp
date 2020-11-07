#include <sstream>
#include <stdexcept>
#include "tokenizer.h"
#include "utils.h"

Token::Token(const Type& type)
	:_type{type}{}

const Type& Token::getType() const { return _type;}

	
StringToken::StringToken(const std::string& val)
	:Token{Type::STRING}, _val{val}{}
			
const std::string& StringToken::getVal() const{
	return _val;
}


IntToken::IntToken(int val)
	:Token{Type::INT}, _val{val}{}
			
const int& IntToken::getVal() const { return _val;}

DoubleToken::DoubleToken(double val)
	:Token{Type::DOUBLE}, _val{val}{}
			
const double& DoubleToken::getVal() const { return _val;}


Tokenizer::Tokenizer(const std::string& str){
	if(str.empty())
		throw std::invalid_argument("Tokenizer: Initialized with empty string");
	
	_tokenizeStream(str);
}

void Tokenizer::_tokenizeStream(const std::string& str){
	std::istringstream ss(str);
	std::string token_str;
	int int_val;
	double double_val;
	
	while( ss >> token_str){
		
		if(StringUtil::StringtoInt(token_str, &int_val)){
			_token_stream.push_back(std::make_unique<IntToken>(int_val));
			continue;
		}

		if(StringUtil::StringtoDouble(token_str, &double_val)){
			_token_stream.push_back(std::make_unique<DoubleToken>(double_val));
			continue;
		}

		_token_stream.push_back(std::make_unique<StringToken>(token_str));
							
	}
}

Token& Tokenizer::getNextTokenVal(Type type){
	if(++_index >= _token_stream.size())
		throw std::out_of_range("The token stream ended can't get next value");
	if (_token_stream[_index]->getType() != type)
		throw std::invalid_argument("wrong type for next token");
	return *_token_stream[_index];
}

Token& Tokenizer::getCurrTokenVal(Type type){
	if (_token_stream[_index]->getType() != type)
		throw std::invalid_argument("wrong type for current token");
	return *_token_stream[_index];
}

Token& Tokenizer::getPrevTokenVal(Type type){
	if(_index == 0)
		throw std::out_of_range("The token stream is inital position. No previous value");
	if (_token_stream[--_index]->getType() != type)
		throw std::invalid_argument("wrong type for current token");
	return *_token_stream[_index];
}

void Tokenizer::resetTokenStream() {_index = 0;}

	
