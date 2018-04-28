// #include "token.hpp"
#include <iostream>

#include "radix.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  Variable a('x'), b('y');
  std::string st = "X";
  a = Int(32.1834926);
  std::cout << a.GetRef() << "," << b.GetRef() << "\n";
  a = Int(3.1415);
  std::cout << a << "::" << b << "\n";
  b = Int(5.1413);
  std::cout << a << "::" << b << "\n";
  a = NULL;
  std::cout << a << "::" << b << "\n";
  // Long a(1), b(3);
  // a /= b;
  // std::cout << a.GetString() << "\n";
  // a *= b;
  // std::cout << a.GetString() << "\n";

  /* code */
  return 0;
}
