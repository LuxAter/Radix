#ifndef RAdIX_EXPRESSION_BASE_HPP_
#define RAdIX_EXPRESSION_BASE_HPP_

#include <string>
#include <memory>

namespace radix {
enum ExpressionType { NONE = 0, VALUE = 1, FUNCTION = 2 };

class ExpressionBase {
 public:
  ExpressionBase();
  ExpressionBase(const ExpressionType& type);
  virtual ~ExpressionBase();

  virtual std::string Latex(bool recurse = false) const;

  ExpressionType type_;
};
}  // namespace radix

#endif  // RAdIX_EXPRESSION_BASE_HPP_
