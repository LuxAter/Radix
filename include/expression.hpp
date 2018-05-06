#ifndef RADIX_EXPRESSION_HPP_
#define RADIX_EXPRESSION_HPP_

#include <memory>
#include <string>
#include <vector>

namespace radix {
enum ExpressionType { VALUE = 1, FUNCTION = 2 };

class Expression {
 public:
  Expression();
  Expression(const ExpressionType& type);
  Expression(const Expression& copy);
  virtual ~Expression();

  void SetVariable(std::string ref, std::shared_ptr<Expression> val);
  void SetVariable(std::shared_ptr<Expression> val);
  // std::shared_ptr<Expression> Eval() const;

  virtual std::string Latex(bool recurse = true) const;
  virtual std::string Tree(std::size_t indent = 2) const;

  void insert(std::size_t pos, std::shared_ptr<Expression> child);
  std::shared_ptr<Expression>& at(std::size_t pos);
  void append(std::shared_ptr<Expression> child);
  void prepend(std::shared_ptr<Expression> child);
  void clear();
  std::vector<std::shared_ptr<Expression>>::iterator begin();
  std::vector<std::shared_ptr<Expression>>::iterator end();
  std::shared_ptr<Expression>& front();
  std::shared_ptr<Expression>& back();

  bool IsLeaf() const;
  bool HasOnlyLeafs() const;

  ExpressionType type_;
  std::shared_ptr<Expression> next_, prev_;
  std::vector<std::shared_ptr<Expression>> children_;

 private:
};

typedef std::shared_ptr<Expression> Exp;
std::shared_ptr<Expression> GenerateExpression(std::string_view str);
std::shared_ptr<Expression> CopyExpression(std::shared_ptr<Expression> exp);
std::shared_ptr<Expression> CopyExpression(const Expression* exp);

std::shared_ptr<Expression> Eval(std::shared_ptr<Expression> exp,
                                 std::vector<std::shared_ptr<Expression>> vals = {});
std::shared_ptr<Expression> Eval_(std::shared_ptr<Expression> exp);
}  // namespace radix

#endif  // RADIX_EXPRESSION_HPP_
