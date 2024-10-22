#ifndef LEXER_H
#define LEXER_H

#include <exception>
#include <istream>
#include <string>
#include <vector>

#include "Lexer/Token.h"

std::vector<Token> tokenize(std::istream &stream);

class ParsingException : public std::exception {
 public:
  ParsingException() = delete;
  ParsingException(const char *msg, const std::string &context, size_t position);
  ~ParsingException();

  virtual const char *what() const noexcept override;

 private:
  std::string m_message{};
};

#endif
