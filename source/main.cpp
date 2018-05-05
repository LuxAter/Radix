// #include "token.hpp"
#include <iostream>

#include "radix.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  math::Initialize(10);
  Exp exp = Operator('+');
  exp->append(Operator('*'));
  exp->back()->append(Long(2));
  exp->back()->append(Operator('^'));
  exp->back()->back()->append(Variable('x'));
  exp->back()->back()->append(Long(3));
  exp->append(Operator('^'));
  exp->back()->append(Function("sin"));
  exp->back()->back()->append(Variable('x'));
  exp->back()->append(Long(1.0/3.0));
  // exp->append(math::pi);
  // exp->append(Operator('^'));
  // exp->back()->append(math::e);
  // exp->back()->append(Function(Function::SIN));
  // exp->back()->back()->append(Variable('x'));
  // exp.children_.push_back(GenerateExpression(""));
  // exp->children_.push_back(Long(3.1415));
  // exp->children_.push_back(Variable('x'));
  std::cout << exp->Tree() << "\n";
  std::cout << exp->Latex() << "\n";
  /* code */
  return 0;
}
