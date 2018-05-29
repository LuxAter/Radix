#include "function/function_base.hpp"

#include <memory>
#include <ostream>

#include "expression_base.hpp"

#include "function/function.hpp"
#include "function/operator.hpp"

radix::FunctionBase::FunctionBase() : ExpressionBase(FUNCTION) {}
radix::FunctionBase::FunctionBase(ExpressionType type)
    : ExpressionBase(type){}
radix::FunctionBase::~FunctionBase() {}

std::shared_ptr<radix::ExpressionBase> radix::FunctionBase::eval(){
  return std::make_shared<ExpressionBase>(ExpressionBase());
}

std::string radix::FunctionBase::Unicode(bool recurse) const{
  return std::string();
}
std::string radix::FunctionBase::Latex(bool recurse) const {
  return std::string();
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
  };
  return out;
}
std::shared_ptr<radix::ExpressionBase> radix::CopyFunction(
    std::shared_ptr<radix::ExpressionBase> exp) {
  std::shared_ptr<FunctionBase> func =
      std::dynamic_pointer_cast<FunctionBase>(exp);
  if (func->type_ == OPERATOR) {
    return Operator(*std::dynamic_pointer_cast<Operator>(func));
  } else if (func->type_ == FUNCTION) {
    return Function(*std::dynamic_pointer_cast<Function>(func));
  }
  return NULL;
}

std::shared_ptr<radix::ExpressionBase> radix::CopyFunction(const ExpressionBase* exp) {
  const FunctionBase* func = dynamic_cast<const FunctionBase*>(exp);
  if (func->type_ == OPERATOR) {
    return Operator(*dynamic_cast<const Operator*>(func));
  } else if (func->type_ == FUNCTION) {
    return Function(*dynamic_cast<const Function*>(func));
  }
  return NULL;
}
