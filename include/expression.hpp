#ifndef RADIX_EXPRESSION_HPP_
#define RADIX_EXPRESSION_HPP_

#include <string>

namespace radix {
enum ExpressionType { EQUATION = 0, VALUE = 1, FUNCTION = 2 };

class Expression {
 public:
  Expression();
  Expression(const ExpressionType& type);
  virtual ~Expression();

  virtual std::string Latex() const;

  ExpressionType type_;

 private:
};
}  // namespace radix

#endif  // RADIX_EXPRESSION_HPP_
