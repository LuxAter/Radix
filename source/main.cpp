// #include "token.hpp"
#include <iostream>

#include "radix.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  Function f("\\Psi");
  f.AddParam('x');
  f.AddParam('y', Int(3.1415));
  f.push_back(Variable('x'));
  std::cout << f.Latex() << "\n";
  std::cout << f({Int(0)}) << "\n";
  /* code */
  return 0;
}
