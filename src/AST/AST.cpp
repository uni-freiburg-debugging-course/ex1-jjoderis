#include "AST.h"
#include "Lexer/Token.h"

ASTreeNode::ASTreeNode() {}

TreeNodeType ASTreeNode::getType() const { return m_type; }
int ASTreeNode::getValue() const {
  if (m_type != NumberNode)
    throw "Invalid access to value member of a node that does not represent a "
          "number!";

  return m_value;
}
OperatorType ASTreeNode::getOperatorType() const {
  if (m_type != OperationNode)
    throw "Invalid access to the operator type of a node that does not "
          "represent an operator!";

  return m_op;
}
const std::vector<ASTreeNode> &ASTreeNode::getChildren() const {
  return m_children;
}

ASTree::ASTree(const std::vector<Token> &tokens) {
  size_t index{0};
  m_root = createExpressionNode(tokens, index);
}

const ASTreeNode &ASTree::getRoot() const { return m_root; }

ASTreeNode ASTree::createExpressionNode(const std::vector<Token> &tokens,
                                        size_t &currentIndex) const {
  ASTreeNode node{};
  node.m_type = ExpressionNode;

  if (tokens[currentIndex++].getType() != LeftBracket)
    throw "Expected a left bracket at the start of an expression";

  node.m_children.push_back(createOperatorNode(tokens, currentIndex));

  if (tokens[currentIndex++].getType() != RightBracket)
    throw "Expected a right bracket at the end of an expression";

  return node;
}

ASTreeNode ASTree::createOperatorNode(const std::vector<Token> &tokens,
                                      size_t &currentIndex) const {
  ASTreeNode node{};
  node.m_type = OperationNode;

  if (tokens[currentIndex].getType() != Operator)
    throw "Expected an operator at the start of an expression!";

  node.m_op = tokens[currentIndex++].getOperatorType();

  if (node.m_op == SIM) {
    node.m_children.push_back(createExpressionNode(tokens, currentIndex));
  } else {
    for (int i = 0; i < 2; ++i) {
      switch (tokens[currentIndex].getType()) {
      case Number:
        node.m_children.push_back(createNumberNode(tokens, currentIndex));
        break;
      case LeftBracket:
        node.m_children.push_back(createExpressionNode(tokens, currentIndex));
        break;
      default:
        throw "Expected either a number or an expression as an argument to an "
              "operator!";
      }
    }
  }

  return node;
}

ASTreeNode ASTree::createNumberNode(const std::vector<Token> &tokens,
                                    size_t &currentIndex) const {
  ASTreeNode node{};
  node.m_type = NumberNode;

  node.m_value = tokens[currentIndex++].getValue();

  return node;
}
