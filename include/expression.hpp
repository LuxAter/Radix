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

      virtual std::string Latex(bool recurse = true) const;
      virtual std::string Tree(std::size_t indent=2) const;

      void insert(std::size_t pos, std::shared_ptr<Expression> child);
      void append(std::shared_ptr<Expression> child);
      void prepend(std::shared_ptr<Expression> child);
      std::vector<std::shared_ptr<Expression>>::iterator begin();
      std::vector<std::shared_ptr<Expression>>::iterator end();
      std::shared_ptr<Expression> front();
      std::shared_ptr<Expression> back();

      ExpressionType type_;
      std::shared_ptr<Expression> parent_, next_, prev_;
      std::vector<std::shared_ptr<Expression>> children_;

    private:
  };

  typedef std::shared_ptr<Expression> Exp;
  std::shared_ptr<Expression> GenerateExpression(std::string_view);
}  // namespace radix

#endif  // RADIX_EXPRESSION_HPP_
