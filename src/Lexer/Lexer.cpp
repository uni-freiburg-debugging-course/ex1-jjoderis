#include "Lexer.h"
#include "Lexer/Token.h"
#include <cctype>
#include <sstream>

/**
 * Syntax:
 *
 * EXPRESSION -> '(' OPERATION ')'
 *
 * OPERATION  -> ADD | MULTIPLY | SUBTRACT | SIMPLIFY
 *
 * ADD        -> '+' ARGUMENT ARGUMENT
 * MULTIPLY   -> '*' ARGUMENT ARGUMENT
 * SUBTRACT   -> '-' ARGUMENT ARGUMENT
 * SIMPLIFY   -> 'simplify' EXPRESSION
 *
 * ARGUMENT   -> NUMBER | EXPRESSION
 *
 * NUMBER     -> int32
 *
 */

Lexer::Lexer() {}

std::vector<Token> &Lexer::parse(const std::string &expression) {
  m_expression = expression;
  m_position = 0;
  m_tokens.clear();
  try {
    parseExpression();
    // TODO: maybe check if there is something else than whitespace after the
    // closing bracket which could be ignored or result in an error
  } catch (const char *msg) {
    throw ParsingException(msg, m_expression, m_position);
  }
  return m_tokens;
}

void Lexer::parseExpression() {
  skipWhiteSpace();
  if (m_expression[m_position] != '(')
    throw "Expected '(' at the start of an expression!";

  m_tokens.push_back(TokenFactory::createLeftBracket());
  ++m_position;

  parseOperation();

  skipWhiteSpace();
  if (m_expression[m_position] != ')')
    throw "Expected ')' at the end of an expression!";

  ++m_position;
  m_tokens.push_back(TokenFactory::createRightBracket());
}

void Lexer::parseOperation() {
  skipWhiteSpace();

  switch (m_expression[m_position]) {
  case '+':
    parseAdd();
    break;
  case '-':
    parseSubtract();
    break;
  case '*':
    parseMultiply();
    break;
  case 's':
    parseSimplify();
    break;
  default:
    throw "Unexpected operator. Expected one of +,-,*,simplify!";
  }
}
void Lexer::parseAdd() {
  ++m_position;
  m_tokens.push_back(TokenFactory::createOperatorToken(ADD));
  parseArguments(2);
}
void Lexer::parseMultiply() {
  ++m_position;
  m_tokens.push_back(TokenFactory::createOperatorToken(MUL));
  parseArguments(2);
}
void Lexer::parseSubtract() {
  ++m_position;
  m_tokens.push_back(TokenFactory::createOperatorToken(SUB));
  parseArguments(2);
}

void Lexer::parseSimplify() {
  std::string expected{"simplify"};

  for (size_t i = 0; i < expected.length(); ++i) {
    if (m_expression[m_position] != expected.at(i)) {
      m_position -= i;
      throw "Unexpected operator. Expected one of +,-,*,simplify!";
    }
    ++m_position;
  }

  m_tokens.push_back(TokenFactory::createOperatorToken(SIM));

  parseExpression();
}

void Lexer::parseArguments(int numArguments) {
  for (int i = 0; i < numArguments; ++i) {
    skipWhiteSpace();

    switch (m_expression[m_position]) {
    case '(':
      parseExpression();
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      parseNumber();
      break;
    default:
      throw "Expected either an expression or a number as the argument of an "
            "operation!";
    }
  }
}

void Lexer::parseNumber() {
  int value = 0;

  while (m_expression.at(m_position) != ')' &&
         !std::isspace(m_expression.at(m_position))) {
    value *= 10;
    switch (m_expression[m_position]) {
    case '0':
      break;
    case '1':
      value += 1;
      break;
    case '2':
      value += 2;
      break;
    case '3':
      value += 3;
      break;
    case '4':
      value += 4;
      break;
    case '5':
      value += 5;
      break;
    case '6':
      value += 6;
      break;
    case '7':
      value += 7;
      break;
    case '8':
      value += 8;
      break;
    case '9':
      value += 9;
      break;
    default:
      throw "Encountered non-numeric character while parsing a number!";
      break;
    }
    m_position++;
  }

  m_tokens.push_back(TokenFactory::createNumberToken(value));
}

void Lexer::skipWhiteSpace() {
  while (m_position < m_expression.length() &&
         std::isspace(m_expression.at(m_position))) {
    ++m_position;
  }
}

ParsingException::ParsingException(const char *msg, const std::string &context,
                                   size_t position) {
  std::stringstream stream;
  stream << msg << " Position (" << position << "): ";
  m_message = stream.str();

  size_t offset = m_message.length();
  std::string pointerLine{"\n"};
  pointerLine.append(offset + position, ' ');
  pointerLine.append("v\n");
  m_message.insert(0, pointerLine);

  m_message.append(context);
}

ParsingException::~ParsingException() {}

const char *ParsingException::what() const noexcept {
  return m_message.c_str();
}
