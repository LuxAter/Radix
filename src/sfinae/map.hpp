#ifndef RADIX_SFINAE_MAP_HPP_
#define RADIX_SFINAE_MAP_HPP_

#include <map>
#include <type_traits>

namespace radix {
namespace sfinae {
  template <typename>
  struct is_map : std::false_type {};
  template <typename _K, typename _V>
  struct is_map<std::map<_K, _V>> : std::true_type {};
}  // namespace sfinae
}  // namespace radix

#endif  // RADIX_SFINAE_MAP_HPP_
