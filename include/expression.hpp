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
      Expression(const Expression& copy);
      virtual ~Expression();

      std::shared_ptr<Expression> Eval() const;

      virtual std::string Latex(bool recurse = true) const;
      virtual std::string Tree(std::size_t indent=2) const;

      void insert(std::size_t pos, std::shared_ptr<Expression> child);
      std::shared_ptr<Expression>& at(std::size_t pos);
      void append(std::shared_ptr<Expression> child);
      void prepend(std::shared_ptr<Expression> child);
      void clear();
      std::vector<std::shared_ptr<Expression>>::iterator begin();
      std::vector<std::shared_ptr<Expression>>::iterator end();
      std::shared_ptr<Expression>& front();
      std::shared_ptr<Expression>& back();

      ExpressionType type_;
      std::shared_ptr<Expression> next_, prev_;
      std::vector<std::shared_ptr<Expression>> children_;

    private:
  };

  typedef std::shared_ptr<Expression> Exp;
  std::shared_ptr<Expression> GenerateExpression(std::string_view str);
  std::shared_ptr<Expression> CopyExpression(std::shared_ptr<Expression> exp);
}  // namespace radix

#endif  // RADIX_EXPRESSION_HPP_
