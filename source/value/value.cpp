#include "value/value.hpp"

#include <memory>
#include <ostream>

#include "expression.hpp"

#include "value/long.hpp"
#include "value/variable.hpp"

radix::Value::Value() : Expression(VALUE), type_(VARIABLE) {}
radix::Value::Value(ValueType type) : Expression(VALUE), type_(type) {}
radix::Value::~Value() {}

std::string radix::Value::Latex() const { return std::string(); }
std::string radix::Value::Tree(std::size_t indent) const {
  std::string ret = "Exp[Value[NULL]]()";
  std::string rep = "\u2502" + std::string(indent, ' ');
  std::string bar;
  for (std::size_t i = 0; i < indent; i++) {
    bar += "\u2500";
  }
  if (children_.size() != 0) {
    ret += "\n";
  }
  for (auto it = children_.begin(); it != children_.end(); ++it) {
    if (it != children_.end() - 1) {
      ret += "\u251c" + bar;
    } else {
      ret += "\u2514" + bar;
      rep = std::string(indent + 1, ' ');
    }
    std::string sub = (*it)->Tree(indent);
    size_t pos = 0;
    while ((pos = sub.find('\n', pos)) != std::string::npos) {
      sub.insert(++pos, rep);
      pos += rep.length();
    }
    ret += sub;
    if (it != children_.end() - 1) {
      ret += "\n";
    }
  }
  return ret;
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

std::shared_ptr<radix::Value> radix::ValueOperation(const std::shared_ptr<Value>& lhs,
                                              const std::shared_ptr<Value>& rhs,
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
