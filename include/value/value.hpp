#ifndef RADIX_VALUE_VALUE_HPP_
#define RADIX_VALUE_VALUE_HPP_

#include "../expression_base.hpp"

#include <memory>
#include <ostream>

namespace radix {
class Value : public ExpressionBase {
 public:
  enum ValueOperator {
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3,
    MOD = 4,
    EQ = 5,
    NEQ = 6,
    LES = 7,
    GRE = 8,
    LEQ = 9,
    GEQ = 10
  };
  Value();
  Value(ExpressionType type);
  virtual ~Value();

  virtual std::string Unicode(bool recurse = true) const;
  virtual std::string Latex(bool recurse = true) const;
};

std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Value>& lhs);

std::shared_ptr<Value> ValueOperation(const std::shared_ptr<Value>& lhs,
                                      const std::shared_ptr<Value>& rhs,
                                      Value::ValueOperator op);
bool ValueComparison(const std::shared_ptr<Value>& lhs,
                     const std::shared_ptr<Value>& rhs,
                     Value::ValueOperator op);
template <typename _Tp>
std::shared_ptr<Value> ValueFunc(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs,
                                 _Tp (*func)(const _Tp&, const _Tp&)) {
  return func(*std::dynamic_pointer_cast<_Tp>(lhs),
              *std::dynamic_pointer_cast<_Tp>(rhs));
}
template <typename _Tp>
std::shared_ptr<Value> ValueFunc(const std::shared_ptr<Value>& lhs,
                                 _Tp (*func)(const _Tp&)) {
  return func(*std::dynamic_pointer_cast<_Tp>(lhs));
}

std::shared_ptr<Value> operator+(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator-(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator*(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator/(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator%(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);

bool operator==(const std::shared_ptr<Value>& lhs,
                const std::shared_ptr<Value>& rhs);
bool operator!=(const std::shared_ptr<Value>& lhs,
                const std::shared_ptr<Value>& rhs);
bool operator<(const std::shared_ptr<Value>& lhs,
               const std::shared_ptr<Value>& rhs);
bool operator>(const std::shared_ptr<Value>& lhs,
               const std::shared_ptr<Value>& rhs);
bool operator<=(const std::shared_ptr<Value>& lhs,
                const std::shared_ptr<Value>& rhs);
bool operator>=(const std::shared_ptr<Value>& lhs,
                const std::shared_ptr<Value>& rhs);

// Basic Operators
//
// ============================================================================
std::shared_ptr<Value> abs(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> fabs(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> max(const std::shared_ptr<Value>& x,
                           const std::shared_ptr<Value>& y);
std::shared_ptr<Value> min(const std::shared_ptr<Value>& x,
                           const std::shared_ptr<Value>& y);

// Exponential Functions
//
// ============================================================================
std::shared_ptr<Value> exp(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> exp2(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> exp10(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> expm1(const std::shared_ptr<Value>& arg);

std::shared_ptr<Value> log(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> log2(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> log10(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> log1p(const std::shared_ptr<Value>& arg);

// Power Functions
//
// ============================================================================
std::shared_ptr<Value> pow(const std::shared_ptr<Value>& base,
                           const std::shared_ptr<Value>& exp);
std::shared_ptr<Value> sqrt(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> cbrt(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> rootn(const std::shared_ptr<Value>& arg,
                             const std::shared_ptr<Value>& k);
std::shared_ptr<Value> hypot(const std::shared_ptr<Value>& x,
                             const std::shared_ptr<Value>& y);

// Trigonometric Functions
//
// ============================================================================
std::shared_ptr<Value> sin(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> cos(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> tan(const std::shared_ptr<Value>& arg);

std::shared_ptr<Value> sec(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> csc(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> cot(const std::shared_ptr<Value>& arg);

std::shared_ptr<Value> acos(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> asin(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> atan(const std::shared_ptr<Value>& arg);

// Hyperbolic Functions
//
// ============================================================================
std::shared_ptr<Value> sinh(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> cosh(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> tanh(const std::shared_ptr<Value>& arg);

std::shared_ptr<Value> sech(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> csch(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> coth(const std::shared_ptr<Value>& arg);

std::shared_ptr<Value> acosh(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> asinh(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> atanh(const std::shared_ptr<Value>& arg);

// Error and Gamma Functions
//
// ============================================================================
std::shared_ptr<Value> erf(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> erfc(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> tgamma(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> lgamma(const std::shared_ptr<Value>& arg);

// Nearest Integer Floating Point Operations
//
// ============================================================================
std::shared_ptr<Value> ceil(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> floor(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> trunc(const std::shared_ptr<Value>& arg);
std::shared_ptr<Value> round(const std::shared_ptr<Value>& arg);

std::shared_ptr<ExpressionBase> CopyValue(std::shared_ptr<ExpressionBase> exp);
std::shared_ptr<ExpressionBase> CopyValue(const ExpressionBase* exp);
}  // namespace radix

#endif  // RADIX_VALUE_VALUE_HPP_
