#ifndef RADIX_VALUE_VALUE_HPP_
#define RADIX_VALUE_VALUE_HPP_

#include "../expression.hpp"

#include <memory>
#include <ostream>

namespace radix {
enum ValueType { VARIABLE = 0, INT = 1 };
enum ValueOperator {
  ADD = 0,
  SUB = 1,
  MUL = 2,
  DIV = 3,
  EQ = 4,
  NEQ = 5,
  LES = 6,
  GRE = 7,
  LEQ = 8,
  GEQ = 9
};
class Value : public Expression {
 public:
  Value();
  Value(ValueType type);
  virtual ~Value();

  virtual std::string Latex() const;

  ValueType type_;
};

std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Value>& lhs);

std::shared_ptr<Value> Operator(const std::shared_ptr<Value>& lhs,
                                const std::shared_ptr<Value>& rhs,
                                ValueOperator op);
bool Comparison(const std::shared_ptr<Value>& lhs,
                const std::shared_ptr<Value>& rhs, ValueOperator op);

std::shared_ptr<Value> operator+(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator-(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator*(const std::shared_ptr<Value>& lhs,
                                 const std::shared_ptr<Value>& rhs);
std::shared_ptr<Value> operator/(const std::shared_ptr<Value>& lhs,
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
}  // namespace radix

#endif  // RADIX_VALUE_VALUE_HPP_
