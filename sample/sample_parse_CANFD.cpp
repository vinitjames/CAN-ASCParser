#include <memory>
#include <chrono>
#include <iostream>
#include "../src/message.h"
#include "../src/ascparser.h"

int main(int argc, char *argv[])
{   
    ASCParser parser("../testdata/testlarge.asc");
	std::unique_ptr<Message> msg;
	auto start = std::chrono::high_resolution_clock::now();
	int id = std::stoi("1bfeba63", nullptr, 16);
	int count = 0;
	while(!parser.fileEnded()){
		
		msg = parser.getMessage();
		if(msg){
			if(msg->arbitration_id() == id)
			    
			    if(msg->_data[11] == 100)count++;
				
		}
	}
	auto duration  = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);
	std::cout<< "time: "<< duration.count() << " count"<<count;
    return 0;
}
