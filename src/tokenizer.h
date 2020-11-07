#include <string>
#include <vector>
#include <memory>

enum class Type{
	STRING,
	INT,
	DOUBLE	
};


class  Token{
public:
	Token() = delete;
	Token(const Type& type);
	virtual ~Token() = default;
	virtual const Type& getType() const;
protected:
	Type _type;
	
};

class StringToken : public Token{
	
public:
	StringToken() = delete;
    StringToken(const std::string& val);
			
	const std::string& getVal() const;

private:
	std::string _val;
	
};

class IntToken : public Token{
	
public:
	IntToken() = delete;
    IntToken(int val);
			
	const int& getVal() const;
private:
	int _val;
};

class DoubleToken : public Token{
	
public:
	DoubleToken() = delete;
    DoubleToken(double val);
			
	const double& getVal() const;
private:
	double _val;
};


class Tokenizer{
public:
	Tokenizer() = delete;
	Tokenizer(const std::string& str);
	Token& getCurrTokenVal(Type type);
	Token& getNextTokenVal(Type type);
	Token& getPrevTokenVal(Type type);
	void resetTokenStream();
	
		
private:
	void _tokenizeStream(const std::string& str);
	std::vector <std::unique_ptr<Token>>_token_stream;
	std::size_t _index = 0;
};

