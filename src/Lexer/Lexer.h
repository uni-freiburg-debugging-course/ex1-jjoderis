#ifndef LEXER_H
#define LEXER_H

#include "Lexer/Token.h"
#include <exception>
#include <string>
#include <vector>

class Lexer {
public:
  Lexer();

  std::vector<Token> &parse(const std::string &expression);

private:
  void parseExpression();

  void parseOperation();

  void parseAdd();
  void parseMultiply();
  void parseSubtract();
  void parseSimplify();

  void parseArguments(int numArguments);

  void parseNumber();

  void skipWhiteSpace();

  std::string m_expression;
  size_t m_position{0};
  std::vector<Token> m_tokens{};
};

class ParsingException : public std::exception {
public:
  ParsingException() = delete;
  ParsingException(const char *msg, const std::string &context,
                   size_t position);
  ~ParsingException();

  virtual const char *what() const noexcept override;

private:
  std::string m_message{};
};

#endif
