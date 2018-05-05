// #include "token.hpp"
#include <iostream>

#include "radix.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  Expression exp;
  exp.children_.push_back(GenerateExpression(""));
  exp.children_.push_back(Long(3.1415));
  exp.children_.push_back(Variable('x'));
  std::cout << exp.Tree() << "\n";
  /* code */
  return 0;
}
