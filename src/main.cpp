#include "radix.hpp"

int main(int argc, char *argv[])
{
  radix::log::Version("Radix V.%d.%d", RADIX_VERSION_MAJOR, RADIX_VERSION_MINOR);
  radix::script::Script lua("test.lua");
  double x, y;
  std::cout << "X?\n";
  std::cin >> x;
  std::cout << lua.call<double>("math.sin", x);
  return 0;
}
