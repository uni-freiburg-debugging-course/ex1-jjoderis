#ifndef LEXER_H
#define LEXER_H

#include <exception>
#include <istream>
#include <string>
#include <vector>

#include "Lexer/Token.h"

std::vector<Token> tokenize(std::istream &stream);

void parseExpression(std::istream &stream, std::vector<Token> &tokens);
void parseNumber(std::istream &stream, std::vector<Token> &tokens);
void parseArguments(int numArguments, std::istream &stream, std::vector<Token> &tokens);
void parseAdd(std::istream &stream, std::vector<Token> &tokens);
void parseMultiply(std::istream &stream, std::vector<Token> &tokens);
void parseSubtract(std::istream &stream, std::vector<Token> &tokens);
void parseSimplify(std::istream &stream, std::vector<Token> &tokens);
void parseOperation(std::istream &stream, std::vector<Token> &tokens);

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
