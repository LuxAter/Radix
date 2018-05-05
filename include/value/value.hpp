#ifndef RADIX_VALUE_VALUE_HPP_
#define RADIX_VALUE_VALUE_HPP_

#include "../expression.hpp"

#include <memory>
#include <ostream>

namespace radix {
enum ValueType { VARIABLE = 0, INT = 1 };
class Value : public Expression {
 public:
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
  Value();
  Value(ValueType type);
  virtual ~Value();

  virtual std::string Latex() const;
  virtual std::string Tree(std::size_t indent = 2) const;

  ValueType type_;
};

std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Value>& lhs);

std::shared_ptr<Value> ValueOperation(const std::shared_ptr<Value>& lhs,
                                const std::shared_ptr<Value>& rhs,
                                Value::ValueOperator op);
bool ValueComparison(const std::shared_ptr<Value>& lhs,
                const std::shared_ptr<Value>& rhs, Value::ValueOperator op);

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
