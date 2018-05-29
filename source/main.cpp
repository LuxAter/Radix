// #include "token.hpp"
#include <iostream>

#include "radix.hpp"

#include "lexer.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  math::Initialize(20);
  std::string expression;
  std::cout << "Enter Expression:";
  std::getline(std::cin, expression);

  Lexer lex;
  lex.LoadOperators();
  lex.LoadFunctions();
  Expression ex = lex.Parse(expression);
  std::cout << Unicode(ex) << "\n";
  Expression ret = Eval(ex, {{"x", Long(17)}});
  std::cout << Unicode(ex) << "\n";
  std::cout << Unicode(ret) << "\n";
  return 0;
}
