#ifndef RADIX_FUNCTION_FUNCTION_BASE_HPP_
#define RADIX_FUNCTION_FUNCTION_BASE_HPP_

#include "../expression.hpp"

#include <memory>
#include <ostream>

namespace radix {
enum FunctionType { OPERATOR = 0, STANDARD = 1, USER = 2 };
class FunctionBase : public Expression {
 public:
  FunctionBase();
  FunctionBase(FunctionType type);
  virtual ~FunctionBase();

  virtual std::shared_ptr<Expression> eval();

  virtual std::string Latex(bool recurse = true) const;
  virtual std::string Tree(std::size_t indent = 2) const;

  FunctionType type_;
};

std::ostream& operator<<(std::ostream& out,
                         const std::shared_ptr<FunctionBase>& lhs);

std::shared_ptr<Expression> CopyFunction(std::shared_ptr<Expression> exp);
std::shared_ptr<Expression> CopyFunction(const Expression* exp);
}  // namespace radix

#endif  // RADIX_FUNCTION_FUNCTION_HPP_
