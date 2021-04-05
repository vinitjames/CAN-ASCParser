#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "gtest/gtest.h"
#include "utils.h"


TEST(UtilsTest, TestStringToInt){	
	int val;
	std::string str_int{"10"};
	EXPECT_EQ(StringUtil::StringtoInt(str_int, &val), true);
	EXPECT_EQ(val, 10);
	str_int = "0";
	EXPECT_EQ(StringUtil::StringtoInt(str_int, &val), true);
	EXPECT_EQ(val, 0);
	str_int = "42356";
	EXPECT_EQ(StringUtil::StringtoInt(str_int, &val), true);
	EXPECT_EQ(val, 42356);
	str_int = "20039";
	EXPECT_EQ(StringUtil::StringtoInt(str_int, &val), true);
	EXPECT_EQ(val, 20039);
	str_int = "";
	EXPECT_EQ(StringUtil::StringtoInt(str_int, &val), false);
	str_int = "10.0";
	EXPECT_EQ(StringUtil::StringtoInt(str_int, &val), false);
}

TEST(UtilsTest, TestStringToDouble){	
	double val;
	std::string str_double{"10.12"};
	EXPECT_EQ(StringUtil::StringtoDouble(str_double, &val), true);
	EXPECT_DOUBLE_EQ(val, 10.12);
	str_double = "0";
	EXPECT_EQ(StringUtil::StringtoDouble(str_double, &val), true);
	EXPECT_DOUBLE_EQ(val, 0);
	str_double = "42356.123";
	EXPECT_EQ(StringUtil::StringtoDouble(str_double, &val), true);
	EXPECT_EQ(val, 42356.123);
	str_double = "42356.12.3";
	EXPECT_EQ(StringUtil::StringtoDouble(str_double, &val), false);	
}

TEST(UtilsTest, TestStringToHex){	
	int val;
	std::string str_hex{"FF"};
	EXPECT_EQ(StringUtil::StringtoHex(str_hex, &val), true);
	EXPECT_EQ(val, 255);
	str_hex = "10";
	EXPECT_EQ(StringUtil::StringtoHex(str_hex, &val), true);
	EXPECT_EQ(val, 16);
	str_hex = "ba253befx";
	EXPECT_EQ(StringUtil::StringtoHex(str_hex, &val), true);	
	EXPECT_EQ(val, -1171964945);
	str_hex = "ba253beh";
	EXPECT_EQ(StringUtil::StringtoHex(str_hex, &val), false);
}

