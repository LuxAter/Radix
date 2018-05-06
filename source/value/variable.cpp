#include "value/variable.hpp"

#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "value/value.hpp"

radix::Variable::Variable() : Value(VARIABLE), ref_(), val_(NULL) {}
radix::Variable::Variable(const std::string& ref_str)
    : Value(VARIABLE), ref_(ref_str), val_(NULL) {}
radix::Variable::Variable(const char& ref_ch)
    : Value(VARIABLE), ref_(1, ref_ch), val_(NULL) {}
radix::Variable::Variable(const std::string& ref_str,
                          std::shared_ptr<Value> val)
    : Value(VARIABLE), ref_(ref_str), val_(val) {}
radix::Variable::Variable(const char& ref_ch, std::shared_ptr<Value> val)
    : Value(VARIABLE), ref_(1, ref_ch), val_(val) {}
radix::Variable::~Variable() {}

void radix::Variable::SetRef(const std::string& ref_str) { ref_ = ref_str; }
void radix::Variable::SetRef(const char& ref_ch) { ref_ = ref_ch; }
void radix::Variable::SetVal(std::shared_ptr<Value> val) { val_ = val; }

std::string radix::Variable::GetRef() const { return ref_; }
std::shared_ptr<radix::Value> radix::Variable::GetVal() const { return val_; }

std::string radix::Variable::Latex(bool recurse) const {
  std::stringstream ss;
  if (val_ != NULL && recurse == true) {
    return val_->Latex();
  } else {
    return ref_;
  }
}
std::string radix::Variable::Tree(std::size_t indent) const {
  std::string ret = "Exp[Value[Variable]](" + Latex(false) + ")";
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

radix::Variable& radix::Variable::operator=(const std::shared_ptr<Value> val) {
  val_ = val;
  return *this;
}

radix::Variable::operator std::shared_ptr<Value>() {
  return std::dynamic_pointer_cast<radix::Value>(
      std::make_shared<Variable>(*this));
}
radix::Variable::operator std::shared_ptr<Expression>() {
  return std::dynamic_pointer_cast<radix::Expression>(
      std::make_shared<Variable>(*this));
}

std::ostream& radix::operator<<(std::ostream& out, const Variable& lhs) {
  if (lhs.GetVal() == NULL) {
    out << lhs.GetRef();
  } else {
    out << lhs.GetVal();
  }
  return out;
}

std::shared_ptr<radix::Value> radix::operator+(const Variable& lhs,
                                               const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return (lhs.GetVal() + rhs.GetVal());
  }
  return NULL;
}
std::shared_ptr<radix::Value> radix::operator-(const Variable& lhs,
                                               const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return (lhs.GetVal() - rhs.GetVal());
  }
  return NULL;
}
std::shared_ptr<radix::Value> radix::operator*(const Variable& lhs,
                                               const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return (lhs.GetVal() * rhs.GetVal());
  }
  return NULL;
}
std::shared_ptr<radix::Value> radix::operator/(const Variable& lhs,
                                               const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return (lhs.GetVal() / rhs.GetVal());
  }
  return NULL;
}

bool radix::operator==(const Variable& lhs, const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return lhs.GetVal() == rhs.GetVal();
  } else {
    return lhs.GetRef() == rhs.GetRef();
  }
}
bool radix::operator!=(const Variable& lhs, const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return lhs.GetVal() != rhs.GetVal();
  } else {
    return lhs.GetRef() != rhs.GetRef();
  }
}
bool radix::operator<(const Variable& lhs, const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return lhs.GetVal() < rhs.GetVal();
  } else {
    return lhs.GetRef() < rhs.GetRef();
  }
}
bool radix::operator>(const Variable& lhs, const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return lhs.GetVal() > rhs.GetVal();
  } else {
    return lhs.GetRef() > rhs.GetRef();
  }
}
bool radix::operator<=(const Variable& lhs, const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return lhs.GetVal() <= rhs.GetVal();
  } else {
    return lhs.GetRef() <= rhs.GetRef();
  }
}
bool radix::operator>=(const Variable& lhs, const Variable& rhs) {
  if (lhs.GetVal() != NULL && rhs.GetVal() != NULL) {
    return lhs.GetVal() >= rhs.GetVal();
  } else {
    return lhs.GetRef() >= rhs.GetRef();
  }
}
