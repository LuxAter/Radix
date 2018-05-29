#ifndef RAdIX_EXPRESSION_BASE_HPP_
#define RAdIX_EXPRESSION_BASE_HPP_

#include <memory>
#include <string>

namespace radix {
enum ExpressionType { NONE, VALUE, VARIABLE, INT, FUNCTION, OPERATOR };

class ExpressionBase {
 public:
  ExpressionBase();
  ExpressionBase(const ExpressionType& type);
  virtual ~ExpressionBase();

  virtual std::string Unicode(bool recurse = false) const;
  virtual std::string Latex(bool recurse = false) const;

  ExpressionType type_;
};
}  // namespace radix

#endif  // RAdIX_EXPRESSION_BASE_HPP_
