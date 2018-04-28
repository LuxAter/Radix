#ifndef RADIX_VALUE_VALUE_HPP_
#define RADIX_VALUE_VALUE_HPP_

#include "../equation_base.hpp"

#include <ostream>
#include <memory>

namespace radix {
  enum ValueType {
    VARIABLE = 0,
    INT = 1
  };
  class Value : public EquationBase{
    public:
    Value();
    Value(ValueType type);
    virtual ~Value();

    ValueType type_;
  };

  std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Value>& lhs);
} // namespace radix

#endif  // RADIX_VALUE_VALUE_HPP_
