#include "value/value.hpp"

#include <memory>
#include <ostream>

#include "expression_base.hpp"

#include "value/long.hpp"
#include "value/variable.hpp"

#define MONOFUNC(func)                                                   \
  std::shared_ptr<radix::Value> radix::func(                             \
      const std::shared_ptr<Value>& arg) {                               \
    switch (arg->type_) {                                                \
      case VARIABLE:                                                     \
        return func(std::dynamic_pointer_cast<Variable>(arg)->GetVal()); \
      case INT:                                                          \
        return ValueFunc<Long>(arg, func);                               \
      default:                                                           \
        return arg;                                                      \
    }                                                                    \
  }

#define DIFUNC(func)                                                          \
  std::shared_ptr<radix::Value> radix::func(                                  \
      const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) { \
    if (lhs->type_ == VARIABLE) {                                             \
      return func(std::dynamic_pointer_cast<Variable>(lhs)->GetVal(), rhs);   \
    } else if (rhs->type_ == VARIABLE) {                                      \
      return func(lhs, std::dynamic_pointer_cast<Variable>(rhs)->GetVal());   \
    }                                                                         \
    switch (lhs->type_) {                                                     \
      case INT:                                                               \
        switch (lhs->type_) {                                                 \
          case INT:                                                           \
            return ValueFunc<Long>(lhs, rhs, func);                           \
          default:                                                            \
            return rhs;                                                       \
        }                                                                     \
      default:                                                                \
        return lhs;                                                           \
    }                                                                         \
  }

radix::Value::Value() : ExpressionBase(VALUE) {}
radix::Value::Value(ExpressionType type) : ExpressionBase(type) {}
radix::Value::~Value() {}

std::string radix::Value::Unicode(bool) const { return std::string(); }
std::string radix::Value::Latex(bool) const { return std::string(); }

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
    default:
      break;
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
    default:
      return NULL;
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
    default:
      return false;
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

// Basic Operators
//
// ============================================================================
MONOFUNC(abs)
MONOFUNC(fabs)
DIFUNC(min)
DIFUNC(max)

// Exponential Functions
//
// ============================================================================
MONOFUNC(exp)
MONOFUNC(exp2)
MONOFUNC(exp10)
MONOFUNC(log)
MONOFUNC(log2)
MONOFUNC(log10)

// Power Functions
//
// ============================================================================
DIFUNC(pow)
MONOFUNC(sqrt)
MONOFUNC(cbrt)
DIFUNC(rootn)
DIFUNC(hypot)

// Trigonometric Functions
//
// ============================================================================
MONOFUNC(sin)
MONOFUNC(cos)
MONOFUNC(tan)
MONOFUNC(sec)
MONOFUNC(csc)
MONOFUNC(cot)
MONOFUNC(acos)
MONOFUNC(asin)
MONOFUNC(atan)

// Hyperbolic Functions
//
// ============================================================================
MONOFUNC(sinh)
MONOFUNC(cosh)
MONOFUNC(tanh)
MONOFUNC(sech)
MONOFUNC(csch)
MONOFUNC(coth)
MONOFUNC(acosh)
MONOFUNC(asinh)
MONOFUNC(atanh)

// Error and Gamma Functions
//
// ============================================================================
MONOFUNC(erf)
MONOFUNC(erfc)
MONOFUNC(tgamma)
MONOFUNC(lgamma)

// Nearest Integer Floating Point Operations
//
// ============================================================================
MONOFUNC(ceil)
MONOFUNC(floor)
MONOFUNC(trunc)
MONOFUNC(round)

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
std::shared_ptr<radix::ExpressionBase> radix::CopyValue(
    const ExpressionBase* exp) {
  const Value* val = dynamic_cast<const Value*>(exp);
  if (val->type_ == VARIABLE) {
    return Variable(*dynamic_cast<const Variable*>(val));
  } else if (val->type_ == INT) {
    return Long(*dynamic_cast<const Long*>(val));
  }
  return NULL;
}
