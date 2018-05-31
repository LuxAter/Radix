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
  std::cout << "Enter X:";
  std::getline(std::cin, expression);
  Expression x = lex.Parse(expression);
  Expression ret = Eval(ex, {{"x", x}});
  std::cout << PrintAST(ex) << "\n";
  std::cout << Unicode(ret) << "\n";
  return 0;
}
