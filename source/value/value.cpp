#include "value/value.hpp"

#include <memory>
#include <ostream>

#include "equation_base.hpp"

#include "value/long.hpp"

radix::Value::Value() : EquationBase(VALUE), type_(VARIABLE) {}
radix::Value::Value(ValueType type) : EquationBase(VALUE), type_(type) {}
radix::Value::~Value() {}

std::ostream& radix::operator<<(std::ostream& out,
                                const std::shared_ptr<Value>& lhs) {
  if (lhs == NULL){
    out << "(null)";
    return out;
  }
  switch (lhs->type_) {
    case VARIABLE: {
      out << "VAR\n";
      break;
    }
    case INT: {
      out << *std::dynamic_pointer_cast<Long>(lhs);
      break;
    }
  };
  return out;
}
