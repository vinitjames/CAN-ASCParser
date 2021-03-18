#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "gtest/gtest.h"
#include "tokenizer.h"


TEST(TokenizerTest, TestEmptyStream){
	try{
		Tokenizer tokenizer("");
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Tokenizer: Initialized with empty string"));
	}	
}

TEST(TokenizerTest, TestTokenizerGetters){	
	Tokenizer tokenizer("this 1 is 171.32 a 3.1423 stream $%#@ of JUnK$");
	EXPECT_TRUE(tokenizer.getCurrToken() == "this");
	try{
		tokenizer.getPrevToken();
		FAIL() << "Expected std::out_of_range"; 
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("The token stream is in inital position. No previous value"));
	}
	
	EXPECT_TRUE(tokenizer.getNextToken() == 1);
	EXPECT_TRUE(tokenizer.getNextToken() == Type::STRING);
	EXPECT_TRUE(tokenizer.getCurrToken() == "is");
	EXPECT_TRUE(tokenizer.getNextToken() == Type::DOUBLE);
	EXPECT_TRUE(tokenizer.getCurrToken() == 171.32);
	EXPECT_TRUE(tokenizer.getNextToken() == "a");
	EXPECT_TRUE(tokenizer.getCurrToken() == Type::STRING);
	EXPECT_TRUE(tokenizer.getNextToken() == 3.1423);
	EXPECT_TRUE(tokenizer.getCurrToken() == Type::DOUBLE);
	EXPECT_FALSE(tokenizer.getCurrToken() == Type::INT);
	EXPECT_FALSE(tokenizer.getNextToken() == Type::INT);
	EXPECT_TRUE(tokenizer.getCurrToken() == "stream");
	EXPECT_TRUE(tokenizer.getPrevToken() == 3.1423);
	EXPECT_TRUE(tokenizer.getNextToken() == Type::STRING);
	EXPECT_TRUE(tokenizer.getNextToken() == Type::STRING);
	EXPECT_TRUE(tokenizer.getCurrToken() == "$%#@");
	EXPECT_TRUE(tokenizer.getNextToken() == "of");
	EXPECT_TRUE(tokenizer.getNextToken() == "JUnK$");
	EXPECT_TRUE(tokenizer.getCurrToken() == Type::STRING);
	EXPECT_FALSE(tokenizer.getCurrToken() == Type::INT);
	EXPECT_FALSE(tokenizer.getCurrToken() == Type::DOUBLE);
	EXPECT_TRUE(tokenizer.getCurrToken() != Type::INT);
	EXPECT_TRUE(tokenizer.getCurrToken() != Type::DOUBLE);

	try{
		tokenizer.getNextToken();
		FAIL() << "Expected std::out_of_range"; 
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("The token stream ended can't get next value"));
	}
	
}

TEST(TokenizerTest, TestTokenizerFrontBack){	
	Tokenizer tokenizer("test stream 23.45");
	EXPECT_TRUE(tokenizer.getCurrToken() == "test");
	EXPECT_TRUE(tokenizer.front() == "test");
	EXPECT_TRUE(tokenizer.front() == Type::STRING);
	EXPECT_TRUE(tokenizer.back() == 23.45);
	EXPECT_TRUE(tokenizer.back() == Type::DOUBLE);
	EXPECT_TRUE(tokenizer.getNextToken() == "stream");	
	EXPECT_TRUE(tokenizer.getNextToken() == "23.45");
	EXPECT_TRUE(tokenizer.back() == "23.45");
	EXPECT_TRUE(tokenizer.front() == "test");	
}

TEST(TokenizerTest, TestTokenizerSize){	
	Tokenizer tokenizer1("test stream #$J@ 123.32 43534");
	EXPECT_EQ(tokenizer1.size(), 5);
	Tokenizer tokenizer2("Size #$@ test");
	EXPECT_EQ(tokenizer2.size(), 3);
	Tokenizer tokenizer3("123 $#%% test %^4%^ tokenizer 88474.73 Stream #$#$# 343434 0.00");
	EXPECT_EQ(tokenizer3.size(), 10);
		
}

TEST(TokenizerTest, TestTokenizerAccessOperator){	
	Tokenizer tokenizer("test stream #$J@ 123.32 43534");
	EXPECT_TRUE(tokenizer[4] == 43534);
	EXPECT_TRUE(tokenizer[4] == Type::INT);
	EXPECT_TRUE(tokenizer[0] == "test");
	EXPECT_TRUE(tokenizer[0] == Type::STRING);
	EXPECT_TRUE(tokenizer[3] == 123.32);
	EXPECT_TRUE(tokenizer[3] == Type::DOUBLE);
	EXPECT_TRUE(tokenizer[2] == "#$J@");
	EXPECT_TRUE(tokenizer[2] == Type::STRING);
	EXPECT_TRUE(tokenizer[1] == "stream");
	EXPECT_TRUE(tokenizer[1] == Type::STRING);
	try{
		tokenizer[5];
		FAIL() << "Expected std::out_of_range"; 
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("index out of range of stream"));
	}

	try{
		tokenizer[-1];
		FAIL() << "Expected std::out_of_range"; 
	}
	catch(const std::out_of_range& err){
		EXPECT_EQ(err.what(), std::string("index out of range of stream"));
	}
	
}



