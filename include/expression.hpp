#ifndef RADIX_EXPRESSION_HPP_
#define RADIX_EXPRESSION_HPP_

#include <string>
#include <vector>
#include <memory>

namespace radix {
  enum ExpressionType { VALUE = 1, FUNCTION = 2 };

  class Expression {
    public:
      Expression();
      Expression(const ExpressionType& type);
      virtual ~Expression();

      virtual std::string Latex() const;
      virtual std::string Tree(std::size_t indent=2) const;

      ExpressionType type_;
      std::shared_ptr<Expression> parent_, next_, prev_;
      std::vector<std::shared_ptr<Expression>> children_;

    private:
  };

  typedef std::shared_ptr<Expression> Exp;
  std::shared_ptr<Expression> GenerateExpression(std::string_view);
}  // namespace radix

#endif  // RADIX_EXPRESSION_HPP_
