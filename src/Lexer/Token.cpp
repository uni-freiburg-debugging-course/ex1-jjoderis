#include "Token.h"

#include <cassert>

Token::Token() {}

TokenType Token::getType() const { return m_type; }
int Token::getValue() const {
  assert(m_type == Number && "Cannot access the value for a token that does not represent a number!");

  return m_value;
}
OperatorType Token::getOperatorType() const {
  assert(m_type == Operator && "Cannot access the operator type of a token that does not represent an operator!");

  return m_op;
}

std::ostream &operator<<(std::ostream &out, const Token &tok) {
  out << "{ type: ";

  switch (tok.getType()) {
    case LeftBracket:
      out << "'(' ";
      break;
    case RightBracket:
      out << "')' ";
      break;
    case Number:
      out << "'Number', ";
      break;
    case Operator:
      out << "'Operator', ";
      break;
  }

  switch (tok.getType()) {
    case Number:
      out << "value: " << tok.getValue() << ' ';
      break;
    case Operator:
      out << "value: ";

      switch (tok.getOperatorType()) {
        case ADD:
          out << "'+' ";
          break;
        case MUL:
          out << "'*' ";
          break;
        case SUB:
          out << "'-' ";
          break;
        case SIM:
          out << "'simplify' ";
          break;
      }

      break;
    default:
      break;
  }

  out << " }";
  return out;
}

Token TokenFactory::createLeftBracket() {
  Token tok{};
  tok.m_type = LeftBracket;
  return tok;
}
Token TokenFactory::createRightBracket() {
  Token tok{};
  tok.m_type = RightBracket;
  return tok;
};
Token TokenFactory::createNumberToken(int value) {
  Token tok{};
  tok.m_type = Number;
  tok.m_value = value;
  return tok;
}
Token TokenFactory::createOperatorToken(OperatorType op) {
  Token tok;
  tok.m_type = Operator;
  tok.m_op = op;
  return tok;
}
