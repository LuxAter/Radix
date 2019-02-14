#ifndef RADIX_SFINAE_VECTOR_HPP_
#define RADIX_SFINAE_VECTOR_HPP_

#include <vector>
#include <type_traits>

namespace radix {
  namespace sfinae {
    template <typename>
      struct is_vector : std::false_type {};

    template <typename _T, typename _A>
      struct is_vector<std::vector<_T, _A>> : std::true_type {};
  } // namespace sfinae
} // namespace radix

#endif  // RADIX_SFINAE_VECTOR_HPP_
