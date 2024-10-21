#include <iostream>
#include <random>
#include <sstream>
#include <vector>

std::string generateExpression(int level);

std::string generateOperand(int level) {

  std::random_device dev;
  std::mt19937 rng(dev());
  // avoid nesting too deep so we do not generate numbers that are too big for
  // an int
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 2);

  int rnd = dist(rng);

  if (level < rnd) {
    return generateExpression(level + 1);
  } else {
    // avoid using large numbers so we do not generate numbers that are too big
    // for an int
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 20);
    std::stringstream stream;
    stream << dist(rng);
    return stream.str();
  }
}

std::string generateExpression(int level) {
  std::stringstream stream;

  std::vector<const char *> operators{"*", "+", "-"};

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(
      0, operators.size() - 1);

  stream << '(' << operators[dist(rng)] << ' ' << generateOperand(level) << ' '
         << generateOperand(level) << ')';

  return stream.str();
}

int main() { std::cout << "(simplify " << generateExpression(0) << ")\n"; }
