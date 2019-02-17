#include "radix.hpp"

int main(int argc, char* argv[]) {
  radix::log::Version("Radix V.%d.%d", RADIX_VERSION_MAJOR,
                      RADIX_VERSION_MINOR);
  std::string script = "%lua\n";
  std::string line = "NULL";
  while(line != ""){
    getline(std::cin, line);
    if(line != ""){
      script += line + '\n';
    }
  }
  std::cout << ">>>   SCRIPT\n" << script << "\n>>>   DONE\n";
  radix::script::Script lua(script);
  std::cout << "fun(5) = " << lua.call<double>("fun", 5);
  return 0;
}
