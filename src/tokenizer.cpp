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

/*void Token::getValue(const Type& type, void* val) const{
	switch (type) {
	case Type::INT: {
		*static_cast<int*>(val) = _getIntValue(); 
		break;
	}
	case Type::DOUBLE: {
		*static_cast<double*>(val) = _getDoubleValue(); 
		break;
	}
	case Type::HEX: {
		*static_cast<int*>(val) = _getHexValue(); 
		break;
	}
default:
	{
		*static_cast<std::string*>(val) = _getStringValue(); 
		break;
	}
	}
	
}
*/

int Token::getIntValue() const {
	if(_type != Type::INT)
		throw std::invalid_argument("Current Token is not of type Int.");
	return _int_val;
}

double Token::getDoubleValue() const {
	if(_type != Type::DOUBLE)
		throw std::invalid_argument("Current Token is not of type Double.");
	return _doub_val;
}

int Token::getHexValue() const {
	if(_type == Type::DOUBLE)
		throw std::invalid_argument("Cannot convert double to hex");
	int val;
	if(!StringUtil::StringtoHex(_str_val, &val))
		throw std::invalid_argument("Cannot convert token to hex ");
	return val;
}

const std::string& Token::getStringValue() const { return _str_val; }


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

void Tokenizer::resetTokenStream() const { _index = 0; }

	
int main(int argc, char *argv[])
{
    Tokenizer tokenizer("0.234 18EBFF00x");

	int i = 0;
	std::string str;
	double db;
	tokenizer.front().getValue(Type::DOUBLE, &db);
	std::cout<<db<<std::endl;
	tokenizer.back().getValue(Type::HEX, &i);
	std::cout<<i<<std::endl;
	tokenizer.getCurrToken().getValue(Type::STRING, &str);
	while(true){
		std::cout<< str<<std::endl;
		tokenizer.getNextToken().getValue(Type::STRING, &str);
	}
    return 0;
}
