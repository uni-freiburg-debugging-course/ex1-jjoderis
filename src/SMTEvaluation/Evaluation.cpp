#include "Evaluation.h"
#include "AST/AST.h"
#include "Lexer/Token.h"
#include <sstream>

int evaluateExpressionNode(const ASTreeNode &node);

int getOperandValue(const ASTreeNode &node) {
  if (node.getType() == NumberNode)
    return node.getValue();
  else
    return evaluateExpressionNode(node);
}

int evaluateOperationNode(const ASTreeNode &node) {
  if (node.getOperatorType() == SIM) {
    return evaluateExpressionNode(node.getChildren()[0]);
  } else {
    int leftOperand = getOperandValue(node.getChildren()[0]);
    int rightOperand = getOperandValue(node.getChildren()[1]);

    switch (node.getOperatorType()) {
    case ADD:
      return leftOperand + rightOperand;
    case MUL:
      return leftOperand * rightOperand;
    case SUB:
      return leftOperand - rightOperand;
    default:
      throw "Cannot handle unknown operand!";
    }
  }
}

int evaluateExpressionNode(const ASTreeNode &node) {
  return evaluateOperationNode(node.getChildren()[0]);
}

std::string evaluateTree(const ASTree &tree) {
  int res = evaluateExpressionNode(tree.getRoot());

  std::stringstream stream;
  if (res < 0)
    stream << "(- " << -res << ')';
  else
    stream << res;

  return stream.str();
}
