#ifndef RADIX_HPP_
#define RADIX_HPP_

#define RADIX_VERSION_MAJOR 0
#define RADIX_VERSION_MINOR 1

#include "log.hpp"
#include "script/script_class.hpp"
#include "plot/plot_class.hpp"

namespace radix {
  void version(unsigned& major, unsigned& minor);
} // namespace radix

#endif  // RADIX_HPP_
