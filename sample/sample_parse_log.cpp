#include <chrono>
#include <iostream>
#include <memory>

#include "canasc/ascparser.h"
#include "canasc/message.h"

int main(int argc, char *argv[]) {
  ASCParser parser("../testdata/testfile.asc");
  std::unique_ptr<Message> msg;
  auto start = std::chrono::high_resolution_clock::now();
  int count = 0;
  while (!parser.fileEnded()) {
    msg = parser.getMessage();
    if (msg) {
      std::cout << "timestamp " << msg->timestamp() << "is fd" << msg->is_fd()
                << " is error frame " << msg->is_error_frame()
                << " is remote frame" << msg->is_remote_frame()
                << " arbitration id " << msg->arbitration_id() << '\n';
    }
  }
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start);
  std::cout << "time: " << duration.count() << " count" << count;
  return 0;
}
