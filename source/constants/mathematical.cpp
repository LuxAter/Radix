#include "constants/mathematical.hpp"

#include "value/long.hpp"

#include <iostream>

namespace radix::math {
Long pi;
Long e;
Long root_2;
}  // namespace radix::math

void radix::math::Initialize(std::size_t prec) {
  Long denom(1, prec);
  Long one(1, prec);
  e = Long(0, prec);
  for (std::size_t i = 1; i < prec + 5; i++) {
    e += one / denom;
    denom *= Long(i, prec);
  }
  root_2 = sqrt(Long(2, prec));
  Long recip(0, prec);
  Long fac4k(1, prec);
  Long fack(1, prec);
  for (std::size_t i = 0; i < prec / 2; i++) {
    Long k(4 * i, prec);
    fac4k *= (k * (k - 1) * (k - 2) * (k - 3));
    fack *= Long(i, prec);
    if(i == 0){
      fac4k = 1;
      fack = 1;
    }
    recip += ((fac4k * (1103 + (26390 * Long(i, prec)))) /
             (pow(fack, 4.0) * pow(396, k)));
  }
  recip *= ((2*root_2)/Long(9801, prec));
  pi = one / recip;
}
