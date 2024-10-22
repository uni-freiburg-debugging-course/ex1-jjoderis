#include "Lexer/Lexer.h"

#include <gtest/gtest.h>

#include <sstream>

#include "Lexer/Token.h"

TEST(Lexer_TEST, parse_number_test) {
  std::stringstream stream1{"345 "};
  std::vector<Token> tokens1{};

  parseNumber(stream1, tokens1);
  EXPECT_EQ(tokens1.size(), 1);
  EXPECT_EQ(tokens1[0].getType(), Number);
  EXPECT_EQ(tokens1[0].getValue(), 345);

  std::stringstream stream2{"124)"};
  std::vector<Token> tokens2{};

  parseNumber(stream2, tokens2);
  EXPECT_EQ(tokens2.size(), 1);
  EXPECT_EQ(tokens2[0].getType(), Number);
  EXPECT_EQ(tokens2[0].getValue(), 124);

  std::stringstream stream3{"124+"};
  std::vector<Token> tokens3{};

  EXPECT_THROW(parseNumber(stream3, tokens3), const char*);
}

TEST(Lexer_TEST, parse_expression) {
  std::stringstream stream1{"(+ 1 2)"};
  std::vector<Token> tokens1{};

  parseExpression(stream1, tokens1);
  EXPECT_EQ(tokens1.size(), 5);
  EXPECT_EQ(tokens1[0].getType(), LeftBracket);

  EXPECT_EQ(tokens1[1].getType(), Operator);
  EXPECT_EQ(tokens1[1].getOperatorType(), ADD);

  EXPECT_EQ(tokens1[2].getType(), Number);
  EXPECT_EQ(tokens1[2].getValue(), 1);

  EXPECT_EQ(tokens1[3].getType(), Number);
  EXPECT_EQ(tokens1[3].getValue(), 2);

  EXPECT_EQ(tokens1[4].getType(), RightBracket);

  std::stringstream stream2{"(- 1 2)"};
  std::vector<Token> tokens2{};

  parseExpression(stream2, tokens2);
  EXPECT_EQ(tokens2.size(), 5);
  EXPECT_EQ(tokens2[0].getType(), LeftBracket);

  EXPECT_EQ(tokens2[1].getType(), Operator);
  EXPECT_EQ(tokens2[1].getOperatorType(), SUB);

  EXPECT_EQ(tokens2[2].getType(), Number);
  EXPECT_EQ(tokens2[2].getValue(), 1);

  EXPECT_EQ(tokens2[3].getType(), Number);
  EXPECT_EQ(tokens2[3].getValue(), 2);

  EXPECT_EQ(tokens2[4].getType(), RightBracket);

  std::stringstream stream3{"(- 1 2)"};
  std::vector<Token> tokens3{};

  parseExpression(stream3, tokens3);
  EXPECT_EQ(tokens3.size(), 5);
  EXPECT_EQ(tokens3[0].getType(), LeftBracket);

  EXPECT_EQ(tokens3[1].getType(), Operator);
  EXPECT_EQ(tokens3[1].getOperatorType(), SUB);

  EXPECT_EQ(tokens3[2].getType(), Number);
  EXPECT_EQ(tokens3[2].getValue(), 1);

  EXPECT_EQ(tokens3[3].getType(), Number);
  EXPECT_EQ(tokens3[3].getValue(), 2);

  EXPECT_EQ(tokens3[4].getType(), RightBracket);

  std::stringstream stream4{"(simplify (* 1 2))"};
  std::vector<Token> tokens4{};

  parseExpression(stream4, tokens4);
  EXPECT_EQ(tokens4.size(), 8);
  EXPECT_EQ(tokens4[0].getType(), LeftBracket);

  EXPECT_EQ(tokens4[1].getType(), Operator);
  EXPECT_EQ(tokens4[1].getOperatorType(), SIM);

  EXPECT_EQ(tokens4[2].getType(), LeftBracket);

  EXPECT_EQ(tokens4[3].getType(), Operator);
  EXPECT_EQ(tokens4[3].getOperatorType(), MUL);

  EXPECT_EQ(tokens4[4].getType(), Number);
  EXPECT_EQ(tokens4[4].getValue(), 1);

  EXPECT_EQ(tokens4[5].getType(), Number);
  EXPECT_EQ(tokens4[5].getValue(), 2);

  EXPECT_EQ(tokens4[6].getType(), RightBracket);
  EXPECT_EQ(tokens4[7].getType(), RightBracket);
}

TEST(Lexer_TEST, tokenize_test) {
  std::stringstream stream1{"(simplify (* 1 2))\n(simplify (- 20 5))\n\n\n"};
  std::vector<Token> tokens1 = tokenize(stream1);

  EXPECT_EQ(tokens1.size(), 8);
  EXPECT_EQ(tokens1[0].getType(), LeftBracket);

  EXPECT_EQ(tokens1[1].getType(), Operator);
  EXPECT_EQ(tokens1[1].getOperatorType(), SIM);

  EXPECT_EQ(tokens1[2].getType(), LeftBracket);

  EXPECT_EQ(tokens1[3].getType(), Operator);
  EXPECT_EQ(tokens1[3].getOperatorType(), MUL);

  EXPECT_EQ(tokens1[4].getType(), Number);
  EXPECT_EQ(tokens1[4].getValue(), 1);

  EXPECT_EQ(tokens1[5].getType(), Number);
  EXPECT_EQ(tokens1[5].getValue(), 2);

  EXPECT_EQ(tokens1[6].getType(), RightBracket);
  EXPECT_EQ(tokens1[7].getType(), RightBracket);
}
