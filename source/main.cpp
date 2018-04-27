// #include "token.hpp"
#include <iostream>

#include "long.hpp"
#include "equation.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  Long a(1), b(3);
  a /= b;
  std::cout << a.GetString() << "\n";
  a *= b;
  std::cout << a.GetString() << "\n";

  /* code */
  return 0;
}
