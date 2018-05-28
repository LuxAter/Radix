#include "value/value.hpp"

#include <memory>
#include <ostream>

#include "expression_base.hpp"

#include "value/long.hpp"
#include "value/variable.hpp"

radix::Value::Value() : ExpressionBase(VALUE), type_(VARIABLE) {}
radix::Value::Value(ValueType type) : ExpressionBase(VALUE), type_(type) {}
radix::Value::~Value() {}

std::string radix::Value::Unicode(bool recurse) const {return std::string();}
std::string radix::Value::Latex(bool recurse) const { return std::string(); }

std::ostream& radix::operator<<(std::ostream& out,
                                const std::shared_ptr<Value>& lhs) {
  if (lhs == NULL) {
    out << "(null)";
    return out;
  }
  switch (lhs->type_) {
    case VARIABLE: {
      out << *std::dynamic_pointer_cast<Variable>(lhs);
      break;
    }
    case INT: {
      out << *std::dynamic_pointer_cast<Long>(lhs);
      break;
    }
  };
  return out;
}

std::shared_ptr<radix::Value> radix::ValueOperation(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs,
    Value::ValueOperator op) {
  if (lhs == NULL || rhs == NULL) {
    return NULL;
  }
  switch (lhs->type_) {
    case VARIABLE: {
      switch (rhs->type_) {
        case VARIABLE: {
          switch (op) {
            case Value::ADD:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() +
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::SUB:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() -
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::MUL:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() *
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::DIV:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() /
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::MOD:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() %
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            default:
              return NULL;
          }
        }
        default: {
          switch (op) {
            case Value::ADD:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() + rhs;
            case Value::SUB:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() - rhs;
            case Value::MUL:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() * rhs;
            case Value::DIV:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() / rhs;
            case Value::MOD:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() % rhs;
            default:
              return NULL;
          }
        }
      }
    }
    case INT: {
      switch (rhs->type_) {
        case INT: {
          switch (op) {
            case Value::ADD:
              return *std::dynamic_pointer_cast<Long>(lhs) +
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::SUB:
              return *std::dynamic_pointer_cast<Long>(lhs) -
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::MUL:
              return *std::dynamic_pointer_cast<Long>(lhs) *
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::DIV:
              return *std::dynamic_pointer_cast<Long>(lhs) /
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::MOD:
              return *std::dynamic_pointer_cast<Long>(lhs) %
                     *std::dynamic_pointer_cast<Long>(rhs);
            default:
              return NULL;
          }
        }
        default: { return NULL; }
      }
    }
  }
  return NULL;
}

bool radix::ValueComparison(const std::shared_ptr<Value>& lhs,
                            const std::shared_ptr<Value>& rhs,
                            Value::ValueOperator op) {
  if (lhs == NULL || rhs == NULL) {
    switch (op) {
      case Value::EQ:
        return lhs.get() == rhs.get();
      default:
        return false;
    }
  }
  switch (lhs->type_) {
    case VARIABLE: {
      switch (rhs->type_) {
        case VARIABLE: {
          switch (op) {
            case Value::EQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() ==
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::NEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() !=
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::LES:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() <
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::GRE:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() >
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::LEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() <=
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case Value::GEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() >=
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            default:
              return false;
          }
        }
        default: {
          switch (op) {
            case Value::EQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() == rhs;
            case Value::NEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() != rhs;
            case Value::LES:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() < rhs;
            case Value::GRE:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() > rhs;
            case Value::LEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() <= rhs;
            case Value::GEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() >= rhs;
            default:
              return false;
          }
        }
      }
    }
    case INT: {
      switch (rhs->type_) {
        case INT: {
          switch (op) {
            case Value::EQ:
              return *std::dynamic_pointer_cast<Long>(lhs) ==
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::NEQ:
              return *std::dynamic_pointer_cast<Long>(lhs) !=
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::LES:
              return *std::dynamic_pointer_cast<Long>(lhs) <
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::GRE:
              return *std::dynamic_pointer_cast<Long>(lhs) >
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::LEQ:
              return *std::dynamic_pointer_cast<Long>(lhs) <=
                     *std::dynamic_pointer_cast<Long>(rhs);
            case Value::GEQ:
              return *std::dynamic_pointer_cast<Long>(lhs) >=
                     *std::dynamic_pointer_cast<Long>(rhs);
            default:
              return false;
          }
        }
        default: { return false; }
      }
    }
  }
  return false;
}

std::shared_ptr<radix::Value> radix::operator+(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return ValueOperation(lhs, rhs, Value::ADD);
}
std::shared_ptr<radix::Value> radix::operator-(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return ValueOperation(lhs, rhs, Value::SUB);
}
std::shared_ptr<radix::Value> radix::operator*(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return ValueOperation(lhs, rhs, Value::MUL);
}
std::shared_ptr<radix::Value> radix::operator/(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return ValueOperation(lhs, rhs, Value::DIV);
}
std::shared_ptr<radix::Value> radix::operator%(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return ValueOperation(lhs, rhs, Value::MOD);
}

bool radix::operator==(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return ValueComparison(lhs, rhs, Value::EQ);
}
bool radix::operator!=(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return ValueComparison(lhs, rhs, Value::NEQ);
}
bool radix::operator<(const std::shared_ptr<Value>& lhs,
                      const std::shared_ptr<Value>& rhs) {
  return ValueComparison(lhs, rhs, Value::LES);
}
bool radix::operator>(const std::shared_ptr<Value>& lhs,
                      const std::shared_ptr<Value>& rhs) {
  return ValueComparison(lhs, rhs, Value::GRE);
}
bool radix::operator<=(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return ValueComparison(lhs, rhs, Value::LEQ);
}
bool radix::operator>=(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return ValueComparison(lhs, rhs, Value::GEQ);
}

// // Basic Operators
// //
// ============================================================================
// std::shared_ptr<radix::Value> radix::abs(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::fabs(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::max(const std::shared_ptr<Value>& x,
//                                          const std::shared_ptr<Value>& y);
// std::shared_ptr<radix::Value> radix::min(const std::shared_ptr<Value>& x,
//                                          const std::shared_ptr<Value>& y);
//
// // Exponential Functions
// //
// ============================================================================
// std::shared_ptr<radix::Value> radix::exp(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::exp2(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::exp10(const std::shared_ptr<Value>&
// arg); std::shared_ptr<radix::Value> radix::expm1(const
// std::shared_ptr<Value>& arg);
//
// std::shared_ptr<radix::Value> radix::log(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::log2(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::log10(const std::shared_ptr<Value>&
// arg); std::shared_ptr<radix::Value> radix::log1p(const
// std::shared_ptr<Value>& arg);
//
// // Power Functions
// //
// ============================================================================
std::shared_ptr<radix::Value> radix::pow(const std::shared_ptr<Value>& base,
                                         const std::shared_ptr<Value>& exp) {
  if (base->type_ == VARIABLE) {
    return pow(std::dynamic_pointer_cast<Variable>(base)->GetVal(), exp);
  } else if (exp->type_ == VARIABLE) {
    return pow(base, std::dynamic_pointer_cast<Variable>(exp)->GetVal());
  }
  switch (base->type_) {
    case INT:
      switch (exp->type_) {
        case INT:
          return ValueFunc<Long>(base, exp, pow);
      }
  }
  return base;
}
// std::shared_ptr<radix::Value> radix::sqrt(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::cbrt(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::rootn(const std::shared_ptr<Value>& arg,
//                                            const unsigned long int k);
// std::shared_ptr<radix::Value> radix::hypot(const std::shared_ptr<Value>& x,
//                                            const std::shared_ptr<Value>& y);
//
// // Trigonometric Functions
// //
// ============================================================================
std::shared_ptr<radix::Value> radix::sin(const std::shared_ptr<Value>& arg) {
  switch (arg->type_) {
    case VARIABLE:
      return sin(std::dynamic_pointer_cast<Variable>(arg)->GetVal());
    case INT:
      return ValueFunc<Long>(arg, sin);
  }
  return arg;
}
// std::shared_ptr<radix::Value> radix::cos(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::tan(const std::shared_ptr<Value>& arg);
//
// std::shared_ptr<radix::Value> radix::sec(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::csc(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::cot(const std::shared_ptr<Value>& arg);
//
// std::shared_ptr<radix::Value> radix::acos(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::asin(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::atan(const std::shared_ptr<Value>& arg);
//
// std::shared_ptr<radix::Value> radix::atan2(const std::shared_ptr<Value>& y,
//                                            const std::shared_ptr<Value>& x);
//
// // Hyperbolic Functions
// //
// ============================================================================
// std::shared_ptr<radix::Value> radix::sinh(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::cosh(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::tanh(const std::shared_ptr<Value>& arg);
//
// std::shared_ptr<radix::Value> radix::sech(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::csch(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::coth(const std::shared_ptr<Value>& arg);
//
// std::shared_ptr<radix::Value> radix::acosh(const std::shared_ptr<Value>&
// arg); std::shared_ptr<radix::Value> radix::asinh(const
// std::shared_ptr<Value>& arg); std::shared_ptr<radix::Value>
// radix::atanh(const std::shared_ptr<Value>& arg);
//
// // Error and Gamma Functions
// //
// ============================================================================
// std::shared_ptr<radix::Value> radix::erf(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::erfc(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::tgamma(const std::shared_ptr<Value>&
// arg); std::shared_ptr<radix::Value> radix::lgamma(const
// std::shared_ptr<Value>& arg);
//
// // Nearest Integer Floating Point Operations
// //
// ============================================================================
// std::shared_ptr<radix::Value> radix::ceil(const std::shared_ptr<Value>& arg);
// std::shared_ptr<radix::Value> radix::floor(const std::shared_ptr<Value>&
// arg); std::shared_ptr<radix::Value> radix::trunc(const
// std::shared_ptr<Value>& arg); std::shared_ptr<radix::Value>
// radix::round(const std::shared_ptr<Value>& arg);

std::shared_ptr<radix::ExpressionBase> radix::CopyValue(
    std::shared_ptr<ExpressionBase> exp) {
  std::shared_ptr<Value> val = std::dynamic_pointer_cast<Value>(exp);
  if (val->type_ == VARIABLE) {
    return Variable(*std::dynamic_pointer_cast<Variable>(val));
  } else if (val->type_ == INT) {
    return Long(*std::dynamic_pointer_cast<Long>(val));
  }
  return NULL;
}
std::shared_ptr<radix::ExpressionBase> radix::CopyValue(const ExpressionBase* exp) {
  const Value* val = dynamic_cast<const Value*>(exp);
  if (val->type_ == VARIABLE) {
    return Variable(*dynamic_cast<const Variable*>(val));
  } else if (val->type_ == INT) {
    return Long(*dynamic_cast<const Long*>(val));
  }
  return NULL;
}
