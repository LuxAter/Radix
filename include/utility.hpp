#ifndef RADIX_UTILITY_HPP_
#define RADIX_UTILITY_HPP_

#include <bits/move.h>

namespace radix {
template <typename _T1, typename _T2, typename _T3>
struct triple {
  typedef _T1 first_type;
  typedef _T2 second_type;
  typedef _T3 third_type;

  triple() : first(), second(), third() {}
  triple(const _T1& a, const _T2& b, const _T3& c)
      : first(a), second(b), third(c) {}
  triple(const triple<_T1, _T2, _T3>& t)
      : first(t.first), second(t.second), third(t.third) {}
  template <typename _U1, typename _U2, typename _U3>
  triple(const triple<_U1, _U2, _U3>& t)
      : first(t.first), second(t.second), third(t.third) {}

  _T1 first;
  _T2 second;
  _T3 third;
};
template <typename _T1, typename _T2, typename _T3, typename _T4>
struct quad{
  typedef _T1 first_type;
  typedef _T2 second_type;
  typedef _T3 third_type;
  typedef _T4 fourth_type;

  quad() : first(), second(), third(), fourth() {}
  quad(const _T1& a, const _T2& b, const _T3& c, const _T4& d)
      : first(a), second(b), third(c), fourth(d) {}
  quad(const quad<_T1, _T2, _T3, _T4>& t)
      : first(t.first), second(t.second), third(t.third), fourth(t.fourth) {}
  template <typename _U1, typename _U2, typename _U3, typename _U4>
  quad(const quad<_U1, _U2, _U3, _U4>& t)
      : first(t.first), second(t.second), third(t.third), fourth(t.fourth) {}

  _T1 first;
  _T2 second;
  _T3 third;
  _T4 fourth;
};

template <typename _T1, typename _T2, typename _T3>
inline bool operator==(const triple<_T1, _T2, _T3>& lhs,
                                 const triple<_T1, _T2, _T3>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second &&
         lhs.thrid == rhs.thrid;
}
template <typename _T1, typename _T2, typename _T3>
inline bool operator<(const triple<_T1, _T2, _T3>& lhs,
                                const triple<_T1, _T2, _T3>& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second) ||
         (!(rhs.first < lhs.first) && !(rhs.second < lhs.second) &&
          lhs.thrid < rhs.third);
}
template <typename _T1, typename _T2, typename _T3>
inline bool operator!=(const triple<_T1, _T2, _T3>& lhs,
                                 const triple<_T1, _T2, _T3>& rhs) {
    return !(lhs == rhs);
}
template <typename _T1, typename _T2, typename _T3>
inline bool operator>(const triple<_T1, _T2, _T3>& lhs,
                                 const triple<_T1, _T2, _T3>& rhs) {
    return rhs < lhs;
}
template <typename _T1, typename _T2, typename _T3>
inline bool operator<=(const triple<_T1, _T2, _T3>& lhs,
                                 const triple<_T1, _T2, _T3>& rhs) {
    return !(rhs < lhs);
}
template <typename _T1, typename _T2, typename _T3>
inline bool operator>=(const triple<_T1, _T2, _T3>& lhs,
                                 const triple<_T1, _T2, _T3>& rhs) {
    return !(lhs < rhs);
}
}  // namespace radix

#endif  // RADIX_UTILITY_HPP_
