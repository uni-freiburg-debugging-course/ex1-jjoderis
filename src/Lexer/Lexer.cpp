#include "Lexer.h"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>

#include "Lexer/Token.h"

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
 * it seems that simplify must and can only be the operator in the root expression
 *
 * whitespace seems to be optional if it is not necessary (e.g. between the brackets of two expression as arguments to
 * an operation and in places where whitespace is valid it seems to not matter how much whitespace is used
 *
 * whitespace is also allowed in front of operators and before closing brackets
 *
 */

char getNextCharacter(std::istream &stream) {
  if (stream.eof()) throw "Unexpected end of input while parsing an expression!";
  char c = stream.get();
  if (c == '\n') throw "Unexpected end of line while parsing an expression!";
  return c;
}

char getExpectedCharacter(char expected, std::istream &stream) {
  char c = getNextCharacter(stream);

  if (c != expected) return 0;

  return c;
}

void skipWhiteSpace(std::istream &stream) {
  while (std::isspace(stream.peek())) {
    getNextCharacter(stream);
  }
}

void parseNumber(std::istream &stream, std::vector<Token> &tokens) {
  int value = 0;

  do {
    value *= 10;
    switch (getNextCharacter(stream)) {
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
  } while (stream.peek() != ')' && !std::isspace(stream.peek()));

  tokens.push_back(TokenFactory::createNumberToken(value));
}

void parseArguments(int numArguments, std::istream &stream, std::vector<Token> &tokens) {
  for (int i = 0; i < numArguments; ++i) {
    skipWhiteSpace(stream);

    switch (stream.peek()) {
      case '(':
        parseExpression(stream, tokens);
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
        parseNumber(stream, tokens);
        break;
      default:
        throw "Expected either an expression or a number as the argument of an "
            "operation!";
    }
  }
}

void parseAdd(std::istream &stream, std::vector<Token> &tokens) {
  tokens.push_back(TokenFactory::createOperatorToken(ADD));
  parseArguments(2, stream, tokens);
}
void parseMultiply(std::istream &stream, std::vector<Token> &tokens) {
  tokens.push_back(TokenFactory::createOperatorToken(MUL));
  parseArguments(2, stream, tokens);
}
void parseSubtract(std::istream &stream, std::vector<Token> &tokens) {
  tokens.push_back(TokenFactory::createOperatorToken(SUB));
  parseArguments(2, stream, tokens);
}

void parseSimplify(std::istream &stream, std::vector<Token> &tokens) {
  std::string expected{"implify"};

  for (size_t i = 0; i < expected.length(); ++i) {
    if (!getExpectedCharacter(expected.at(i), stream)) {
      // move the stream backwards for the error message to show the start of the simplify string as the point of the
      // unknown operation
      stream.seekg(-(i + 1), stream.cur);
      throw "Unexpected operator. Expected one of +,-,*,simplify!";
    }
  }

  if (!std::isspace(stream.peek())) {
    stream.seekg(-7, stream.cur);
    throw "Unexpected operator. Expected one of +,-,*,simplify!";
  }

  tokens.push_back(TokenFactory::createOperatorToken(SIM));

  parseExpression(stream, tokens);
}

void parseOperation(std::istream &stream, std::vector<Token> &tokens) {
  skipWhiteSpace(stream);

  switch (getNextCharacter(stream)) {
    case '+':
      parseAdd(stream, tokens);
      break;
    case '-':
      parseSubtract(stream, tokens);
      break;
    case '*':
      parseMultiply(stream, tokens);
      break;
    case 's':
      parseSimplify(stream, tokens);
      break;
    default:
      throw "Unexpected operator. Expected one of +,-,*,simplify!";
  }
}

void parseExpression(std::istream &stream, std::vector<Token> &tokens) {
  skipWhiteSpace(stream);
  char c = getExpectedCharacter('(', stream);
  if (!c) throw "Expected '(' at the start of an expression!";

  tokens.push_back(TokenFactory::createLeftBracket());

  parseOperation(stream, tokens);

  skipWhiteSpace(stream);
  c = getExpectedCharacter(')', stream);
  if (!c) throw "Expected ')' at the end of an expression!";

  tokens.push_back(TokenFactory::createRightBracket());
}

bool skipEmptiness(std::istream &stream) {
  while (std::isspace(stream.peek()) && !stream.eof()) {
    char s = stream.get();
    if (s == '\n') return true;
  }

  if (stream.eof()) return true;

  return false;
}

std::vector<Token> tokenize(std::istream &stream) {
  std::vector<Token> tokens{};

  if (skipEmptiness(stream)) return tokens;

  try {
    parseExpression(stream, tokens);
    skipEmptiness(stream);
    // TODO: maybe check if there is something else than whitespace after the
    // closing bracket which could be ignored or result in an error
  } catch (const char *msg) {
    // show the expression for which parsing failed and mark the char at which parsing failed
    int errorPos = stream.tellg();
    while (stream.tellg() && stream.peek() != '\n') stream.seekg(-1, stream.cur);
    if (stream.peek() == '\n') stream.get();
    int startPos = stream.tellg();
    std::string context{};

    while (!stream.eof() && stream.peek() != '\n') {
      context.append(1, stream.get());
    }

    throw ParsingException(msg, context, errorPos - startPos - 1);
  }

  return tokens;
}

ParsingException::ParsingException(const char *msg, const std::string &context, size_t position) {
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

const char *ParsingException::what() const noexcept { return m_message.c_str(); }
