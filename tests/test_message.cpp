#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include "gtest/gtest.h"
#include "canasc/message.h"

class MessageTest : public ::testing::Test{
public:
	MessageTest(){
		int n;
		std::srand(unsigned(std::time(nullptr)));
		test_data = std::vector<uint8_t>(64);
		std::generate(test_data.begin(), test_data.end(), [](){return std::rand() % 255;});
		std::vector<uint8_t> test_data_copy{test_data};
		std::istringstream{"1bfeba63"} >> std::hex >> n;
		message.arbitration_id(n); 
		message.bit_rate_switch(true);
		message.channel(8);
		message.dlc(64);
		message.error_state_indicator(false);
		message.is_error_frame(false); 
		message.is_extended(true);
		message.is_fd(true);
		message.is_remote_frame(false);
		message.is_rx(true);
		message.timestamp(1613952000000);
		message.data(std::move(test_data_copy));
	}
	
protected:
	Message message;
	std::vector<uint8_t> test_data;
};

TEST_F(MessageTest, CheckArbitrationId){
	std::stringstream ss;
	ss << std::hex << message.arbitration_id();
	ASSERT_EQ(ss.str() , "1bfeba63");
}

TEST_F(MessageTest, CheckBitRateSwitch){ 
	EXPECT_EQ(message.bit_rate_switch(), true);
}

TEST_F(MessageTest, CheckChannel){ 
	EXPECT_EQ(message.channel(), 8);
}

TEST_F(MessageTest, CheckDlc){ 
	EXPECT_EQ(message.dlc(), 64);
}

TEST_F(MessageTest, CheckErrorStateIndicator){ 
	EXPECT_EQ(message.error_state_indicator(), false);
}

TEST_F(MessageTest, CheckExtended){ 
	EXPECT_EQ(message.is_extended(), true);
}

TEST_F(MessageTest, CheckFD){ 
	EXPECT_EQ(message.is_fd(), true);
}

TEST_F(MessageTest, CheckRemoteFrame){ 
	EXPECT_EQ(message.is_remote_frame(), false);
}

TEST_F(MessageTest, CheckRx){ 
	EXPECT_EQ(message.is_rx(), true);
}

TEST_F(MessageTest, CheckTimestamp){ 
	EXPECT_EQ(message.timestamp(), 1613952000000);
}

TEST_F(MessageTest, CheckData){ 
	EXPECT_EQ(message.data(), test_data);
}

