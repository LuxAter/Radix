#ifndef RADIX_VALUE_LONG_HPP_
#define RADIX_VALUE_LONG_HPP_

#include <mpfr.h>

#include <ostream>
#include <string>
#include <memory>

#include "value.hpp"

namespace radix {

enum RoundingMode {
  NEAREST = MPFR_RNDN,
  RNDN = MPFR_RNDN,
  TO_ZERO = MPFR_RNDZ,
  RNDZ = MPFR_RNDZ,
  PLUS_INFINITY = MPFR_RNDU,
  RNDU = MPFR_RNDU,
  MINUS_INFINITY = MPFR_RNDD,
  RNDD = MPFR_RNDD,
  AWAY_ZERO = MPFR_RNDA,
  RNDA = MPFR_RNDA,
  FAITHFUL = MPFR_RNDF,
  RNDF = MPFR_RNDF
};

class Long : public Value {
 public:
  Long();
  Long(int val);
  Long(long int val);
  Long(long long int val);
  Long(unsigned int val);
  Long(unsigned long int val);
  Long(unsigned long long int val);
  Long(float val);
  Long(double val);
  Long(long double val);
  Long(std::string val);
  Long(const char* val);
  Long(int val, std::size_t prec);
  Long(long int val, std::size_t prec);
  Long(long long int val, std::size_t prec);
  Long(unsigned int val, std::size_t prec);
  Long(unsigned long int val, std::size_t prec);
  Long(unsigned long long int val, std::size_t prec);
  Long(float val, std::size_t prec);
  Long(double val, std::size_t prec);
  Long(long double val, std::size_t prec);
  Long(std::string val, std::size_t prec);
  Long(const char* val, std::size_t prec);

  Long(const Long& copy);
  Long(const Long& copy, std::size_t prec);

  virtual ~Long();

  void Set(int val);
  void Set(long int val);
  void Set(long long int val);
  void Set(unsigned int val);
  void Set(unsigned long int val);
  void Set(unsigned long long int val);
  void Set(float val);
  void Set(double val);
  void Set(long double val);
  void Set(std::string val);
  void Set(const char* val);
  void Set(const Long& copy);

  void Data(mpfr_t& val) const;

  std::size_t GetPrecision() const;
  void SetPrecision(std::size_t bits);

  std::string GetString(int prec = -1, bool left=false) const;

  virtual std::string Latex(bool recurse = true) const;
  // virtual std::string Tree(std::size_t indent = 2) const;

  Long& operator=(int val);
  Long& operator=(long int val);
  Long& operator=(long long int val);
  Long& operator=(unsigned int val);
  Long& operator=(unsigned long int val);
  Long& operator=(unsigned long long int val);
  Long& operator=(float val);
  Long& operator=(double val);
  Long& operator=(long double val);
  Long& operator=(std::string val);
  Long& operator=(const char* val);
  Long& operator=(const Long& val);

  Long& operator+=(const Long& rhs);
  Long& operator-=(const Long& rhs);
  Long& operator*=(const Long& rhs);
  Long& operator/=(const Long& rhs);

  operator std::shared_ptr<Value>();
  operator std::shared_ptr<ExpressionBase>();

  mpfr_t value_;

 private:
};

std::ostream& operator<<(std::ostream& out, const Long& lhs);

// Comparison Operators
// ============================================================================
bool operator==(const Long& lhs, const Long& rhs);
bool operator!=(const Long& lhs, const Long& rhs);
bool operator<(const Long& lhs, const Long& rhs);
bool operator>(const Long& lhs, const Long& rhs);
bool operator<=(const Long& lhs, const Long& rhs);
bool operator>=(const Long& lhs, const Long& rhs);

// Arithmetic Operators
// ============================================================================
Long operator+(const Long& lhs, const Long& rhs);
Long operator-(const Long& lhs, const Long& rhs);
Long operator*(const Long& lhs, const Long& rhs);
Long operator/(const Long& lhs, const Long& rhs);
Long operator%(const Long& lhs, const Long& rhs);

// Basic Operators
// ============================================================================
Long abs(const Long& arg);
Long fabs(const Long& arg);
Long max(const Long& x, const Long& y);
Long min(const Long& x, const Long& y);

// Exponential Functions
// ============================================================================
Long exp(const Long& arg);
Long exp2(const Long& arg);
Long exp10(const Long& arg);
Long expm1(const Long& arg);

Long log(const Long& arg);
Long log2(const Long& arg);
Long log10(const Long& arg);
Long log1p(const Long& arg);

// Power Functions
// ============================================================================
Long pow(const Long& base, const Long& exp);
Long sqrt(const Long& arg);
Long cbrt(const Long& arg);
Long rootn(const Long& arg, const unsigned long int k);
Long hypot(const Long& x, const Long& y);

// Trigonometric Functions
// ============================================================================
Long sin(const Long& arg);
Long cos(const Long& arg);
Long tan(const Long& arg);

Long sec(const Long& arg);
Long csc(const Long& arg);
Long cot(const Long& arg);

Long acos(const Long& arg);
Long asin(const Long& arg);
Long atan(const Long& arg);

Long atan2(const Long& y, const Long& x);

// Hyperbolic Functions
// ============================================================================
Long sinh(const Long& arg);
Long cosh(const Long& arg);
Long tanh(const Long& arg);

Long sech(const Long& arg);
Long csch(const Long& arg);
Long coth(const Long& arg);

Long acosh(const Long& arg);
Long asinh(const Long& arg);
Long atanh(const Long& arg);

// Error and Gamma Functions
// ============================================================================
Long erf(const Long& arg);
Long erfc(const Long& arg);
Long tgamma(const Long& arg);
Long lgamma(const Long& arg);

// Nearest Integer Floating Point Operations
// ============================================================================
Long ceil(const Long& arg);
Long floor(const Long& arg);
Long trunc(const Long& arg);
Long round(const Long& arg);
Long rint(const Long& arg, const RoundingMode& rnd);

typedef Long Int;

}  // namespace radix

#endif  // RADIX_VALUE_LONG_HPP_
