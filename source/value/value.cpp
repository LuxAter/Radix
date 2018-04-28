#include "value/value.hpp"

#include <memory>
#include <ostream>

#include "expression.hpp"

#include "value/long.hpp"
#include "value/variable.hpp"

radix::Value::Value() : Expression(VALUE), type_(VARIABLE) {}
radix::Value::Value(ValueType type) : Expression(VALUE), type_(type) {}
radix::Value::~Value() {}

std::string radix::Value::Latex() const {
  if (type_ == INT) {
    return "VI";
  }
  return "V";
}

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

std::shared_ptr<radix::Value> radix::Operator(const std::shared_ptr<Value>& lhs,
                                              const std::shared_ptr<Value>& rhs,
                                              ValueOperator op) {
  if (lhs == NULL || rhs == NULL) {
    return NULL;
  }
  switch (lhs->type_) {
    case VARIABLE: {
      switch (rhs->type_) {
        case VARIABLE: {
          switch (op) {
            case ADD:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() +
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case SUB:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() -
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case MUL:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() *
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case DIV:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() /
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            default:
              return NULL;
          }
        }
        default: {
          switch (op) {
            case ADD:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() + rhs;
            case SUB:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() - rhs;
            case MUL:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() * rhs;
            case DIV:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() / rhs;
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
            case ADD:
              return *std::dynamic_pointer_cast<Long>(lhs) +
                     *std::dynamic_pointer_cast<Long>(rhs);
            case SUB:
              return *std::dynamic_pointer_cast<Long>(lhs) -
                     *std::dynamic_pointer_cast<Long>(rhs);
            case MUL:
              return *std::dynamic_pointer_cast<Long>(lhs) *
                     *std::dynamic_pointer_cast<Long>(rhs);
            case DIV:
              return *std::dynamic_pointer_cast<Long>(lhs) /
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

bool radix::Comparison(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs, ValueOperator op) {
  if (lhs == NULL || rhs == NULL) {
    switch (op) {
      case EQ:
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
            case EQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() ==
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case NEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() !=
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case LES:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() <
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case GRE:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() >
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case LEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() <=
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            case GEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() >=
                     std::dynamic_pointer_cast<Variable>(rhs)->GetVal();
            default:
              return false;
          }
        }
        default: {
          switch (op) {
            case EQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() == rhs;
            case NEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() != rhs;
            case LES:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() < rhs;
            case GRE:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() > rhs;
            case LEQ:
              return std::dynamic_pointer_cast<Variable>(lhs)->GetVal() <= rhs;
            case GEQ:
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
            case EQ:
              return *std::dynamic_pointer_cast<Long>(lhs) ==
                     *std::dynamic_pointer_cast<Long>(rhs);
            case NEQ:
              return *std::dynamic_pointer_cast<Long>(lhs) !=
                     *std::dynamic_pointer_cast<Long>(rhs);
            case LES:
              return *std::dynamic_pointer_cast<Long>(lhs) <
                     *std::dynamic_pointer_cast<Long>(rhs);
            case GRE:
              return *std::dynamic_pointer_cast<Long>(lhs) >
                     *std::dynamic_pointer_cast<Long>(rhs);
            case LEQ:
              return *std::dynamic_pointer_cast<Long>(lhs) <=
                     *std::dynamic_pointer_cast<Long>(rhs);
            case GEQ:
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
  return Operator(lhs, rhs, ADD);
}
std::shared_ptr<radix::Value> radix::operator-(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return Operator(lhs, rhs, SUB);
}
std::shared_ptr<radix::Value> radix::operator*(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return Operator(lhs, rhs, MUL);
}
std::shared_ptr<radix::Value> radix::operator/(
    const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
  return Operator(lhs, rhs, DIV);
}

bool radix::operator==(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return Comparison(lhs, rhs, EQ);
}
bool radix::operator!=(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return Comparison(lhs, rhs, NEQ);
}
bool radix::operator<(const std::shared_ptr<Value>& lhs,
                      const std::shared_ptr<Value>& rhs) {
  return Comparison(lhs, rhs, LES);
}
bool radix::operator>(const std::shared_ptr<Value>& lhs,
                      const std::shared_ptr<Value>& rhs) {
  return Comparison(lhs, rhs, GRE);
}
bool radix::operator<=(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return Comparison(lhs, rhs, LEQ);
}
bool radix::operator>=(const std::shared_ptr<Value>& lhs,
                       const std::shared_ptr<Value>& rhs) {
  return Comparison(lhs, rhs, GEQ);
}
