#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "gtest/gtest.h"
#include "token.h"


TEST(TokenTest, TestIntTokenType){	
	Token token("10");	
	EXPECT_EQ(token.getType(), Type::INT);
	EXPECT_NE(token.getType(), Type::NONE);
	EXPECT_NE(token.getType(), Type::DOUBLE);
	EXPECT_NE(token.getType(), Type::HEX);
	EXPECT_NE(token.getType(), Type::STRING);	
}

TEST(TokenTest, TestIntTokenValue){	
	Token token("98676");	
	EXPECT_EQ(token.getIntValue(), 98676);
	EXPECT_EQ(token.getStringValue(), "98676");
	try{
		double val = token.getDoubleValue();
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Token is not of type Double."));
	}
}

TEST(TokenTest, TestIntTokenEqualOp){	
	Token token1("2354632");
	Token token2("2354632");	
	EXPECT_TRUE(token1 == Type::INT);
	EXPECT_TRUE(token1 == 2354632);
	EXPECT_TRUE(token1 == "2354632");
	EXPECT_TRUE(token1 == token2);
	EXPECT_FALSE(token1 == Type::STRING);
	EXPECT_FALSE(token1 == Type::DOUBLE);
	EXPECT_FALSE(token1 == 23546.32);		
}

TEST(TokenTest, TestIntTokenUnEqualOp){	
	Token token1("5654398");
	Token token2("23433");	
	EXPECT_FALSE(token1 != Type::INT);
	EXPECT_FALSE(token1 != 5654398);
	EXPECT_FALSE(token1 != "5654398");
	EXPECT_TRUE(token1 != token2);
	EXPECT_TRUE(token1 != Type::STRING);
	EXPECT_TRUE(token1 != Type::DOUBLE);
	EXPECT_TRUE(token1 != 56543.98);		
}

TEST(TokenTest, TestDoubleTokenType){	
	Token token("123.01");	
	EXPECT_EQ(token.getType(), Type::DOUBLE);
	EXPECT_NE(token.getType(), Type::NONE);
	EXPECT_NE(token.getType(), Type::INT);
	EXPECT_NE(token.getType(), Type::HEX);
	EXPECT_NE(token.getType(), Type::STRING);	
}

TEST(TokenTest, TestDoubleTokenValue){	
	Token token("1234.00");	
	EXPECT_EQ(token.getDoubleValue(), 1234.00);
	EXPECT_EQ(token.getStringValue(), "1234.00");
	try{
		int val = token.getIntValue();
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Token is not of type Int."));
	}
}

TEST(TokenTest, TestDoubleTokenEqualOp){	
	Token token1("235.4632");
	Token token2("235.4632");	
	EXPECT_TRUE(token1 == Type::DOUBLE);
	EXPECT_TRUE(token1 == 235.4632);
	EXPECT_TRUE(token1 == "235.4632");
	EXPECT_TRUE(token1 == token2);
	EXPECT_FALSE(token1 == Type::STRING);
	EXPECT_FALSE(token1 == Type::INT);
	EXPECT_FALSE(token1 == 23546.32);		
}

TEST(TokenTest, TestDoubleTokenUnEqualOp){	
	Token token1("5654.398");
	Token token2("5654.39");	
	EXPECT_FALSE(token1 != Type::DOUBLE);
	EXPECT_FALSE(token1 != 5654.398);
	EXPECT_FALSE(token1 != "5654.398");
	EXPECT_TRUE(token1 != token2);
	EXPECT_TRUE(token1 != Type::STRING);
	EXPECT_TRUE(token1 != Type::INT);
	EXPECT_TRUE(token1 != 56543.98);		
}

TEST(TokenTest, TestStringTokenType){	
	Token token("testtoken");	
	EXPECT_EQ(token.getType(), Type::STRING);
	EXPECT_NE(token.getType(), Type::NONE);
	EXPECT_NE(token.getType(), Type::INT);
	EXPECT_NE(token.getType(), Type::HEX);
	EXPECT_NE(token.getType(), Type::DOUBLE);	
}

TEST(TokenTest, TestStringTokenValue){	
	Token token("123.4.00,$%");
	EXPECT_EQ(token.getStringValue(), "123.4.00,$%");
	try{
		int val = token.getIntValue();
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Token is not of type Int."));
	}
	
	try{
		double val = token.getDoubleValue();
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Token is not of type Double."));
	}
}

TEST(TokenTest, TestStringTokenEqualOp){	
	Token token1("token0.0.1");
	Token token2("token0.0.1");	
	EXPECT_TRUE(token1 == Type::STRING);
	EXPECT_TRUE(token1 == "token0.0.1");
	EXPECT_TRUE(token1 == token2);
	EXPECT_FALSE(token1 == Type::DOUBLE);
	EXPECT_FALSE(token1 == Type::INT);
	EXPECT_FALSE(token1 == 23546);		
}

TEST(TokenTest, TestStringTokenUnEqualOp){	
	Token token1("test_token1");
	Token token2("test_token2");	
	EXPECT_FALSE(token1 != Type::STRING);
	EXPECT_FALSE(token1 != "test_token1");
	EXPECT_TRUE(token1 != token2);
	EXPECT_TRUE(token1 != Type::DOUBLE);
	EXPECT_TRUE(token1 != Type::INT);
	EXPECT_TRUE(token1 != 56543.98);
	EXPECT_TRUE(token1 != 6474);
}



