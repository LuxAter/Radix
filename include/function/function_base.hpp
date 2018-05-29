#ifndef RADIX_FUNCTION_FUNCTION_BASE_HPP_
#define RADIX_FUNCTION_FUNCTION_BASE_HPP_

#include "../expression_base.hpp"

#include <memory>
#include <ostream>

namespace radix {
class FunctionBase : public ExpressionBase {
 public:
  FunctionBase();
  FunctionBase(ExpressionType type);
  virtual ~FunctionBase();

  virtual std::shared_ptr<ExpressionBase> eval();

  virtual std::string Unicode(bool recurse = true) const;
  virtual std::string Latex(bool recurse = true) const;
  // virtual std::string Tree(std::size_t indent = 2) const;
};

std::ostream& operator<<(std::ostream& out,
                         const std::shared_ptr<FunctionBase>& lhs);

std::shared_ptr<ExpressionBase> CopyFunction(std::shared_ptr<ExpressionBase> exp);
std::shared_ptr<ExpressionBase> CopyFunction(const ExpressionBase* exp);
}  // namespace radix

#endif  // RADIX_FUNCTION_FUNCTION_HPP_
