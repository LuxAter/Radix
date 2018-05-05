#ifndef RADIX_CONSTANTS_MATHEMATICAL_HPP_
#define RADIX_CONSTANTS_MATHEMATICAL_HPP_

#include "../value/long.hpp"

namespace radix {
  namespace math {
    extern Long pi;
    extern Long e;
    extern Long root_2;
    void Initialize(std::size_t prec = sizeof(int) * 8);
  } // namespace math
} // namespace radix

#endif  // RADIX_CONSTANTS_MATHEMATICAL_HPP_
