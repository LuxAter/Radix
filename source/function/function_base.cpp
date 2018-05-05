#include "function/function_base.hpp"

#include <memory>
#include <ostream>

#include "expression.hpp"

#include "function/operator.hpp"
#include "function/function.hpp"

radix::FunctionBase::FunctionBase() : Expression(FUNCTION), type_(USER) {}
radix::FunctionBase::FunctionBase(FunctionType type)
    : Expression(FUNCTION), type_(type) {}
radix::FunctionBase::~FunctionBase() {}

std::string radix::FunctionBase::Latex(bool recurse) const { return std::string(); }
std::string radix::FunctionBase::Tree(std::size_t indent) const {
  std::string ret = "Exp[Function[NULL]]()";
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
                                const std::shared_ptr<FunctionBase>& lhs) {
  if (lhs == NULL) {
    out << "(null)";
    return out;
  }
  switch (lhs->type_) {
    case OPERATOR: {
      out << *std::dynamic_pointer_cast<Operator>(lhs);
      break;
    }
    case STANDARD: {
      // out << *std::dynamic_pointer_cast<Standard>(lhs);
      break;
    }
    case USER: {
      // out << *std::dynamic_pointer_cast<User>(lhs);
      break;
    }
  };
  return out;
}
std::shared_ptr<radix::Expression> radix::CopyFunction(std::shared_ptr<radix::Expression> exp){
  std::shared_ptr<FunctionBase> func = std::dynamic_pointer_cast<FunctionBase>(exp);
  if(func->type_ == OPERATOR){
    return Operator(*std::dynamic_pointer_cast<Operator>(func));
  }else if(func->type_ == STANDARD){
    return Function(*std::dynamic_pointer_cast<Function>(func));
  }
  return NULL;
}
