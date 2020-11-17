#ifndef ASCPARSER_H
#define ASCPARSER_H

#include <fstream>
#include <memory>
#include <string>

#include "message.h"

class Tokenizer;
class Token;

class ASCParser {
 public:
  //! Default constructor
  ASCParser(const std::string& filename);

  //! Copy constructor
  ASCParser(const ASCParser& other) {}

  //! Move constructor
  ASCParser(ASCParser&& other) noexcept {}

  //! Destructor
  virtual ~ASCParser() noexcept;

  //! Copy assignment operator
  ASCParser& operator=(const ASCParser& other);

  //! Move assignment operator
  ASCParser& operator=(ASCParser&& other) noexcept;
  void reinit();
  std::unique_ptr<Message> getMessage();
  Message parseCANFD(const Tokenizer& tokenizer);
  Message parseCAN(const Tokenizer& tokenizer);
  bool fileEnded();

 private:
  bool parseHeader();
  bool checkHeader();
  int getArbitrationID(const Token& token);
  int getBase();
  bool checkTimestamp(const Tokenizer& tokenized_frame);
  bool isCANFD(const Tokenizer& tokenized_frame);
  bool isCAN(const Tokenizer& tokenized_frame);
  int parseCANRemote(const Tokenizer& tokenized_frame);
  bool loadNextStream();
  std::vector<uint8_t> parseDataFromString(const Tokenizer& tokenized_frame,
                                           size_t length);
  
  std::ifstream _ifs;
  std::string _currStream;
  std::string _date;
  std::string _base;
  std::string _timestamp_format;
  std::string _filename;
  bool _internal_events_logged = false;
  bool _eof_reached = false;
};

#endif /* ASCPARSER_H */
