#include "radix.hpp"

int main(int argc, char* argv[]) {
  radix::log::Version("Radix V.%d.%d", RADIX_VERSION_MAJOR,
                      RADIX_VERSION_MINOR);
  radix::plot::Figure fig;
  fig.bmp("test.bmp", 500, 500);
  return 0;
}
