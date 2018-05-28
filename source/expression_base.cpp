#include "expression_base.hpp"

#include <string>
#include <memory>

radix::ExpressionBase::ExpressionBase(){}
radix::ExpressionBase::ExpressionBase(const ExpressionType& type): type_(type){}
radix::ExpressionBase::~ExpressionBase(){}

std::string radix::ExpressionBase::Latex(bool recurse) const {
  return std::string();
}
