#ifndef RADIX_FUNCTION_OPERATOR_HPP_
#define RADIX_FUNCTION_OPERATOR_HPP_

#include <memory>
#include <ostream>

#include "function.hpp"

namespace radix {
class Operator : public Function {
 public:
enum OperatorOp {
  NONE = 0,
  ADD = 1,
  SUB = 2,
  MUL = 3,
  DIV = 4,
  MOD = 5,
  POW = 7,
  FAC = 8
};
  Operator();
  Operator(OperatorOp op);
  Operator(char op);
  Operator(std::string op);

  Operator(const Operator& copy);

  virtual ~Operator();

  virtual std::string Latex() const;
  virtual std::string Tree(std::size_t indent = 2) const;

  operator std::shared_ptr<Function>();
  operator std::shared_ptr<Expression>();

  OperatorOp op_;
 private:
  void ParseChar(char op);
};

std::ostream& operator<<(std::ostream& out,
                         const std::shared_ptr<Operator>& lhs);
}  // namespace radix

#endif  // RADIX_FUNCTION_OPERATOR_HPP_
