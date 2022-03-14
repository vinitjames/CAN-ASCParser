#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "gtest/gtest.h"
#include "ascparser.h"
#include "message.h"

TEST(ASCParserTest, TestFilenameType){
	try{
		ASCParser ascparser("wrong_filename.txt");
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Filename is not of .asc type"));
	}

	try{
		ASCParser ascparser("wrong_filename.asc");
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Could not open given .asc file"));
	}

	try{
		ASCParser ascparser("wrong_filename.Asc");
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Could not open given .asc file"));
	}

	try{
		ASCParser ascparser("wrong_filename.ASC");
		FAIL() << "Expected std::invalid_argument"; 
	}
	catch(const std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("Could not open given .asc file"));
	}
		
}

TEST(ASCParserTest, TestParseHeader){
	try{
		ASCParser ascparser("data/test_wrong_header1.asc");
		FAIL() << "Expected std::domain_error"; 
	}
	catch(const std::domain_error& err){
		EXPECT_EQ(err.what(), std::string("asc file with wrong header"));
	}
	
	try{
		ASCParser ascparser("data/test_wrong_header2.asc");
		FAIL() << "Expected std::domain_error"; 
	}
	catch(const std::domain_error& err){
		EXPECT_EQ(err.what(), std::string("asc file with wrong header"));
	}

	try{
		ASCParser ascparser("data/test_wrong_header3.asc");
		FAIL() << "Expected std::domain_error"; 
	}
	catch(const std::domain_error& err){
		EXPECT_EQ(err.what(), std::string("asc file with wrong header"));
	}

	
	ASCParser ascparser("data/testfile.asc");
	EXPECT_EQ(ascparser.weekday(), "Sam");
	EXPECT_EQ(ascparser.month(), "Sep");
	EXPECT_EQ(ascparser.day(), "30");
	EXPECT_EQ(ascparser.startTime(), "15:06:13.191");
	EXPECT_EQ(ascparser.year(),"2017");
	EXPECT_EQ(ascparser.base(), "hex");
	EXPECT_NE(ascparser.base(), "dec");
	EXPECT_EQ(ascparser.timestamp_format(), "absolute");
	EXPECT_NE(ascparser.timestamp_format(), "relative");
	EXPECT_EQ(ascparser.internal_events_logged(), true);
	EXPECT_NE(ascparser.internal_events_logged(), false);
	
}

TEST(ASCParserTest, TestErrorFrame){

	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_error_frame(), true);
	EXPECT_EQ(msg->timestamp(), 2.501000);
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 0);
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_error_frame(), true);
	EXPECT_EQ(msg->timestamp(), 2.501010);
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 0);
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_error_frame(), true);
	EXPECT_EQ(msg->timestamp(), 2.501020);
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 1);
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_error_frame(), false);
	EXPECT_EQ(msg->timestamp(), 2.510001);
}

TEST(ASCParserTest, TestCanRemoteFrame){

	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 1);
	EXPECT_EQ(msg->is_remote_frame(), true);
	EXPECT_EQ(msg->is_rx(), false);
	EXPECT_EQ(msg->timestamp(), 2.510001);
	EXPECT_EQ(msg->arbitration_id(), 256);
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_remote_frame(), true);
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 2);
	EXPECT_EQ(msg->is_rx(), false);
	EXPECT_EQ(msg->timestamp(), 2.520002);
	EXPECT_EQ(msg->arbitration_id(), 512);
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_remote_frame(), true);
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 3);
	EXPECT_EQ(msg->is_rx(), false);
	EXPECT_EQ(msg->timestamp(), 2.584921);
	EXPECT_EQ(msg->arbitration_id(), 768);
	EXPECT_EQ(msg->dlc(), 8);
}

TEST(ASCParserTest, TestCanFrame1){

	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(msg=ascparser.getMessage()){
		if((!msg->is_remote_frame())&&(!msg->is_error_frame()))
			break;
	}
 
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 0);
	EXPECT_EQ(msg->is_remote_frame(), false);
	EXPECT_EQ(msg->is_rx(), true);
	EXPECT_EQ(msg->timestamp(), 3.098426);
	EXPECT_EQ(msg->arbitration_id(), 418119424);
	EXPECT_EQ(msg->dlc(), 8);
	std::vector<std::string> testfile_data{"1", "A0", "0F", "A6", "60", "3B", "D1", "40"};
	EXPECT_EQ(testfile_data.size(), msg->data().size());
	for(int i=0; i<testfile_data.size(); i++){
		int val;
		std::stringstream ss{testfile_data[i]};
		ss >> std::hex >> val;
		EXPECT_EQ(val, msg->data()[i]);	
	}
}

TEST(ASCParserTest, TestCanFrame2){
	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(msg=ascparser.getMessage()){
		if((!msg->is_remote_frame())&&(!msg->is_error_frame()))
			break;
	}
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 0);
	EXPECT_EQ(msg->is_remote_frame(), false);
	EXPECT_EQ(msg->is_rx(), true);
	EXPECT_EQ(msg->timestamp(), 3.148421);
	EXPECT_EQ(msg->arbitration_id(), 418119424);
	EXPECT_EQ(msg->dlc(), 8);
	std::vector<std::string> testfile_data{"02", "1F", "DE", "80", "25", "DF", "C0", "2B"};
	EXPECT_EQ(testfile_data.size(), msg->data().size());
	for(int i=0; i<testfile_data.size(); i++){
		int val;
		std::stringstream ss{testfile_data[i]};
		ss >> std::hex >> val;
		EXPECT_EQ(val, msg->data()[i]);	
	}
	
}

TEST(ASCParserTest, TestCanFrame3){
	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(msg=ascparser.getMessage()){
		if((!msg->is_remote_frame())&&(!msg->is_error_frame()))
			break;
	}
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_fd(), false);
	EXPECT_EQ(msg->channel(), 0);
	EXPECT_EQ(msg->is_remote_frame(), false);
	EXPECT_EQ(msg->is_rx(), true);
	EXPECT_EQ(msg->timestamp(), 3.248765);
	EXPECT_EQ(msg->arbitration_id(), 418119424);
	EXPECT_EQ(msg->dlc(), 8);
	std::vector<std::string> testfile_data{"04", "00", "4B", "FF", "FF", "FF", "FF", "FF"};
	EXPECT_EQ(testfile_data.size(), msg->data().size());
	for(int i=0; i<testfile_data.size(); i++){
		int val;
		std::stringstream ss{testfile_data[i]};
		ss >> std::hex >> val;
		EXPECT_EQ(val, msg->data()[i]);	
	}
	
}

TEST(ASCParserTest, TestCanFDFrame1){
	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(!msg->is_fd())
		msg = ascparser.getMessage();

	EXPECT_EQ(msg->is_fd(), true);
	EXPECT_EQ(msg->channel(), 1);
	EXPECT_EQ(msg->is_remote_frame(), false);
	EXPECT_EQ(msg->is_rx(), true);
	EXPECT_EQ(msg->timestamp(), 30.005071);
	EXPECT_EQ(msg->arbitration_id(), 768);
	EXPECT_EQ(msg->bit_rate_switch(), true);
	EXPECT_EQ(msg->error_state_indicator(), false);
	EXPECT_EQ(msg->dlc(), 8);
	
	std::vector<std::string> testfile_data{"01", "02", "03", "04", "05", "06", "07", "08"};
	EXPECT_EQ(testfile_data.size(), msg->data().size());
	for(int i=0; i<testfile_data.size(); i++){
		int val;
		std::stringstream ss{testfile_data[i]};
		ss >> std::hex >> val;
		EXPECT_EQ(val, msg->data()[i]);	
	}
	
}

TEST(ASCParserTest, TestCanFDFrame2){
	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(!msg->is_fd())
		msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_fd(), true);
	EXPECT_EQ(msg->channel(), 2);
	EXPECT_EQ(msg->is_remote_frame(), true);
	EXPECT_EQ(msg->is_rx(), false);
	EXPECT_EQ(msg->timestamp(), 30.300981);
	EXPECT_EQ(msg->arbitration_id(), 327685);
	EXPECT_EQ(msg->bit_rate_switch(), false);
	EXPECT_EQ(msg->error_state_indicator(), false);
	EXPECT_EQ(msg->dlc(), 5);
	EXPECT_EQ(msg->data().size(), 0);
	
}

TEST(ASCParserTest, TestCanFDFrame3){
	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(!msg->is_fd())
		msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_fd(), true);
	EXPECT_EQ(msg->channel(), 3);
	EXPECT_EQ(msg->is_remote_frame(), false);
	EXPECT_EQ(msg->is_rx(), true);
	EXPECT_EQ(msg->timestamp(), 30.506898);
	EXPECT_EQ(msg->arbitration_id(), 1262);
	EXPECT_EQ(msg->bit_rate_switch(), false);
	EXPECT_EQ(msg->error_state_indicator(), false);
	EXPECT_EQ(msg->dlc(), 15);
	std::vector<std::string> testfile_data{"01", "02", "03", "04", "00", "00", "00",
		"00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00",
		"00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00",
		"00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00",
		"00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00", "00",
		"00", "00", "00", "00", "64"};
	EXPECT_EQ(testfile_data.size(), msg->data().size());
	for(int i=0; i<testfile_data.size(); i++){
		int val;
		std::stringstream ss{testfile_data[i]};
		ss >> std::hex >> val;
		EXPECT_EQ(val, msg->data()[i]);	
	}	
}

TEST(ASCParserTest, TestCanFDFrame4){
	ASCParser ascparser("data/testfile.asc");
	std::unique_ptr<Message> msg = ascparser.getMessage();
	while(!msg->is_fd())
		msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	msg = ascparser.getMessage();
	EXPECT_EQ(msg->is_fd(), true);
	EXPECT_EQ(msg->channel(), 4);
	EXPECT_EQ(msg->is_error_frame(), true);
	EXPECT_EQ(msg->is_rx(), false);
	EXPECT_EQ(msg->timestamp(), 30.806898);
	
}



