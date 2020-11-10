#include <sstream>
#include <stdexcept>
#include "tokenizer.h"
#include "utils.h"
#include <iostream>


Token::Token(const std::string& str_val)
	:_str_val{str_val}{
	if(StringUtil::StringtoInt(_str_val, &_int_val)){
		_type = Type::INT;
		}
	else if(StringUtil::StringtoDouble(_str_val, &_doub_val)){
		_type = Type::DOUBLE;
		 }
	else
		_type = Type::STRING;
}

bool Token::operator==(const Token& other) const{
	return (_type == other._type)&&(_str_val == other._str_val);
}

bool Token::operator==(const std::string& str_val) const{
	return (_str_val == str_val);
}

bool Token::operator==(const Type& type) const{
	return (_type == type);
}

bool Token::operator==(const int& int_val) const{
	return(_type == Type::INT)&&(_int_val == int_val);
}

bool Token::operator==(const double& double_val) const{
	return(_type == Type::DOUBLE)&&(_doub_val == double_val);
}

bool Token::operator!=(const Token& other) const{
	return (_type != other._type)||(_str_val != other._str_val);
}

bool Token::operator!=(const std::string& str_val) const{
	return (_str_val != str_val);
}

bool Token::operator!=(const Type& type) const{
	return (_type != type);
}

bool Token::operator!=(const int& int_val) const{
	return(_type != Type::INT)||(_int_val != int_val);
}

bool Token::operator!=(const double& double_val) const{
	return(_type != Type::DOUBLE)||(_doub_val != double_val);
}

const Type& Token::getType() const { return _type;}

void Token::getValue(const Type& type, void* val) const{

	if(type == Type::HEX){
			
		}
		
	else if(type != _type)
		throw std::invalid_argument("Token type cannot be converted to {type}");
	
	_getBaseValue(type, val);

	}


void Token::_getBaseValue(const Type &type, void* val) const {
	switch (type) {
	case Type::INT: {
		*(int*)val = _int_val;
		break;
	}
	case Type::DOUBLE:{
		*(double*)val = _int_val;
		break;
	}
	default:{
	*(std::string*)val = _str_val;
	break;
	}
	}
}

Tokenizer::Tokenizer(const std::string& str){
	if(str.empty())
		throw std::invalid_argument("Tokenizer: Initialized with empty string");
	_tokenizeStream(str);
}

void Tokenizer::_tokenizeStream(const std::string& str){
	std::istringstream ss(str);
	std::string token_str;
	while( ss >> token_str)
	 _token_stream.push_back(Token(token_str));							
}

Token& Tokenizer::operator[](const std::size_t index){
	if((index < 0)||(index > _token_stream.size()))
		throw::std::out_of_range("index out of range of stream");
	return _token_stream[index];				   
}

const Token& Tokenizer:: operator[](const std::size_t index) const {
	if((index < 0)||(index > _token_stream.size()))
		throw::std::out_of_range("index out of range of stream");
	return _token_stream[index];
}

Token& Tokenizer::front() { return _token_stream.front(); }

Token& Tokenizer::back() { return _token_stream.back(); }

const Token& Tokenizer::front() const { return _token_stream.front(); }

const Token& Tokenizer::back() const { return _token_stream.back(); }

std::size_t Tokenizer::size() const { return _token_stream.size(); }

Token& Tokenizer::getNextToken(){
	if(++_index >= _token_stream.size())
		throw std::out_of_range("The token stream ended can't get next value");
	return _token_stream[_index];
}

Token& Tokenizer::getCurrToken() { return _token_stream[_index]; }

Token& Tokenizer::getPrevToken(){
	if(_index == 0)
		throw std::out_of_range("The token stream is inital position. No previous value");
	return _token_stream[--_index];
}

const Token& Tokenizer::getNextToken() const {
	if(++_index >= _token_stream.size())
		throw std::out_of_range("The token stream ended can't get next value");
	return _token_stream[_index];
}

const Token& Tokenizer::getCurrToken() const { return _token_stream[_index]; }

const Token& Tokenizer::getPrevToken() const {
	if(_index == 0)
		throw std::out_of_range("The token stream is inital position. No previous value");
	return _token_stream[--_index];
}

void Tokenizer::resetTokenStream() {_index = 0;}

	
int main(int argc, char *argv[])
{
    Tokenizer tokenizer("this is a 20 dollor value");
	while(true){
	try{
		std::cout<<*(std::string*)(tokenizer.getNextToken().getVal())<<std::endl;
			}
	catch(std::exception& e){
		std::cout<<tokenizer.getCurrToken().getVal()<<std::endl;
	}
	}
    return 0;
}
