#ifndef AST_H
#define AST_H

#include "Lexer/Token.h"
#include <vector>
enum TreeNodeType {
  ExpressionNode,
  OperationNode,
  NumberNode,
};

class ASTree;

class ASTreeNode {
public:
  TreeNodeType getType() const;
  int getValue() const;
  OperatorType getOperatorType() const;
  const std::vector<ASTreeNode> &getChildren() const;

private:
  ASTreeNode();

  TreeNodeType m_type;
  union {
    int m_value;
    OperatorType m_op;
  };

  std::vector<ASTreeNode> m_children{};

  friend class ASTree;
};

class ASTree {
public:
  ASTree() = delete;

  ASTree(const std::vector<Token> &tokens);

  const ASTreeNode &getRoot() const;

private:
  ASTreeNode createExpressionNode(const std::vector<Token> &tokens,
                                  size_t &currentIndex) const;
  ASTreeNode createOperatorNode(const std::vector<Token> &tokens,
                                size_t &currentIndex) const;
  ASTreeNode createNumberNode(const std::vector<Token> &tokens,
                              size_t &currentIndex) const;

  ASTreeNode m_root;
};

#endif
