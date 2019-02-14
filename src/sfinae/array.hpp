#ifndef RADIX_SFINAE_ARRAY_HPP_
#define RADIX_SFINAE_ARRAY_HPP_

#include <array>
#include <type_traits>

namespace radix {
namespace sfinae {
  template <typename>
  struct is_array : std::false_type {};

  template <typename _T, std::size_t _N>
  struct is_array<std::array<_T, _N>> : std::true_type {};
}  // namespace sfinae
}  // namespace radix

#endif  // RADIX_SFINAE_ARRAY_HPP_
