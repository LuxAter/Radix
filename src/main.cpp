#include "radix.hpp"

int main(int argc, char* argv[]) {
  radix::log::Version("Radix V.%d.%d", RADIX_VERSION_MAJOR,
                      RADIX_VERSION_MINOR);
  radix::script::Script lua("test.lua");
  std::cout << lua.call<double>("func", 1.0, "hello", 5) << '\n';
  return 0;
}
