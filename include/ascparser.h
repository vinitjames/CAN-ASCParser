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

  //! Destructor
  virtual ~ASCParser() noexcept;

  void reinit();
  std::unique_ptr<Message> getMessage();
  Message parseCANFD(const Tokenizer& tokenizer);
  Message parseCAN(const Tokenizer& tokenizer);
  bool fileEnded();
	const std::string& startTime() const;
	const std::string& weekday() const;
	const std::string& year() const;
	const std::string& month() const;
	const std::string& day() const;
	const std::string& base() const;
	const std::string& timestamp_format() const;
	bool internal_events_logged() const;

 private:
  bool parseHeader();
  bool checkHeader();
  void parseDate();
  int getArbitrationID(const Token& token);
  int getBase();
  bool checkTimestamp(const Tokenizer& tokenized_frame);
  bool isCANFD(const Tokenizer& tokenized_frame);
  bool isCAN(const Tokenizer& tokenized_frame);
  int parseCANRemote(const Tokenizer& tokenized_frame);
  bool loadNextStream();
  static std::string getFileExtension(const std::string& filepath); 
  std::vector<uint8_t> parseDataFromString(const Tokenizer& tokenized_frame,
                                           size_t length);
	struct Date {
		std::string weekday;
		std::string day;
		std::string month;
		std::string time;
		std::string year;		
	}_date;
	
  std::ifstream _ifs;
  std::string _currStream;
  std::string _base;
  std::string _timestamp_format;
  std::string _filename;
  bool _internal_events_logged = false;
  bool _eof_reached = false;
};

#endif /* ASCPARSER_H */
