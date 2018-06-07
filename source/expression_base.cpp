#include "expression_base.hpp"

#include <string>
#include <memory>

radix::ExpressionBase::ExpressionBase(){}
radix::ExpressionBase::ExpressionBase(const ExpressionType& type): type_(type){}
radix::ExpressionBase::~ExpressionBase(){}

std::string radix::ExpressionBase::Unicode(bool) const {
  return std::string();
}
std::string radix::ExpressionBase::Latex(bool) const {
  return std::string();
}
