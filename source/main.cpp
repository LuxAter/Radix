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
  // std::cout << PrintAST(ex) << '\n';
  // std::cout << Unicode(ex) << '\n';
  // std::cout << Latex(ex) << "\n";
  std::cout << PrintDot(ex) << '\n';
  // lex.SetExpression(expression);
  // std::string token = "";
  // while(token != "EOS"){
  //   token = lex.GetNextToken();
  //   std::cout << token << "<<\n";
  // }

  // Exp exp = ParseLatex(expression);
  // Exp exp = Operator('^');
  // exp->append(Function("sin"));
  // exp->back()->append(Variable('x'));
  // exp->append(Long(2));
  // exp->append(Operator('*'));
  // exp->back()->append(Long(2, 20));
  // exp->back()->append(Operator('^'));
  // exp->back()->back()->append(Variable('x'));
  // exp->back()->back()->append(Long(3));
  // exp->append(Operator('^'));
  // exp->back()->append(Function("sin"));
  // exp->back()->back()->append(Variable('x'));
  // exp->back()->append(Long(1.0 / 3.0, 20));
  // std::cout << exp->Latex() << "\n";
  // for (int i = -10; i < 10; i++) {
  //   std::cout << i << ":" << Eval(exp, {Variable('x', Long(i))})->Latex() << "\n";
  // }
  return 0;
}
