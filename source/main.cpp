// #include "token.hpp"
#include <iomanip>
#include <iostream>
#include "long.hpp"

#include <cmath>

using namespace radix;

int main(int argc, char const* argv[]) {
  Long a(
      "3."
      "141592653589793238462643383279502884197169399375105820974944592307816406"
      "2862089986280348253421170679");
  a += 5;
  std::cout << a.GetString(20) << "\n";
  a = pow(a, 2);
  std::cout << a.GetString(20) << "\n";
  a = sqrt(a);
  std::cout << a.GetString(20) << "\n";

  /* code */
  return 0;
}
