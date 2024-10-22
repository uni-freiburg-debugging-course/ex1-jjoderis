#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>

enum TokenType { LeftBracket, RightBracket, Number, Operator };
enum OperatorType { ADD, SUB, MUL, SIM };

class TokenFactory;

class Token {
 public:
  TokenType getType() const;
  int getValue() const;
  OperatorType getOperatorType() const;

 private:
  Token();

  TokenType m_type;
  union {
    int m_value;
    OperatorType m_op;
  };

  friend class TokenFactory;
};

class TokenFactory {
 public:
  static Token createLeftBracket();
  static Token createRightBracket();
  static Token createNumberToken(int value);
  static Token createOperatorToken(OperatorType op);
};

std::ostream &operator<<(std::ostream &out, const Token &tok);

#endif
