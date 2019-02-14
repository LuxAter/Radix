#include "radix.hpp"

int main(int argc, char* argv[]) {
  radix::log::Version("Radix V.%d.%d", RADIX_VERSION_MAJOR,
                      RADIX_VERSION_MINOR);
  radix::script::Script lua("test.lua");
  return 0;
}
