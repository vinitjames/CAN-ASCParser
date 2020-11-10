#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <memory>

enum class Type{
	STRING,
	INT,
	DOUBLE,
	HEX
};


class  Token{
public:
	Token() = delete;
	Token(const std::string& val);
	virtual ~Token() = default;
	virtual const Type& getType() const;
	virtual void getValue(const Type& type, void* val) const;
	bool operator==(const Token& other) const;
	bool operator==(const Type& type) const;
	bool operator==(const std::string& other) const;
	bool operator==(const int& val) const;
	bool operator==(const double& val) const;
	bool operator!=(const Token& other) const;
	bool operator!=(const Type& type) const;
	bool operator!=(const std::string& other) const;
	bool operator!=(const int& val) const;
	bool operator!=(const double& val) const;
	
	
protected:
	void _getBaseValue(const Type& type, void* val) const;
	void _getHexValue(void* val)const;
	Type _type;
	std::string _str_val;
	int _int_val = 0;
	double _doub_val = 0;
	
};


class Tokenizer{
public:
	Tokenizer() = delete;
	Tokenizer(const std::string& str);
	Token& getCurrToken();
	Token& getNextToken();
	Token& getPrevToken();
	const Token& getCurrToken() const;
	const Token& getNextToken() const;
	const Token& getPrevToken() const;
	void resetTokenStream();
	Token& front();
	Token& back();
	const Token& front() const;
	const Token& back() const;
	std::size_t size()const;
	Token& operator[](const std::size_t index);
	const Token& operator[](const std::size_t index) const;
	
	// add [] operator and front and back and length
		
private:
	void _tokenizeStream(const std::string& str);
	std::vector <Token>_token_stream;
	mutable std::size_t _index = 0;
};

#endif /* TOKENIZER_H */
