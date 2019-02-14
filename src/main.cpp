#include "radix.hpp"

int main(int argc, char* argv[]) {
  radix::log::Version("Radix V.%d.%d", RADIX_VERSION_MAJOR,
                      RADIX_VERSION_MINOR);
  radix::script::Script lua("test.lua");
  std::array<double, 10> arr = lua.get<std::array<double, 10>>("arr");
  for(auto& it : arr){
    std::cout << it << ",";
  }
  return 0;
}
