#ifndef RADIX_FUNCTION_FUNCTION_HPP_
#define RADIX_FUNCTION_FUNCTION_HPP_

#include <memory>
#include <ostream>

#include "function_base.hpp"

namespace radix {
class Function : public FunctionBase {
 public:
  enum FunctionNames {
    NONE = 0,
    LOG_2 = 1,
    LOG = 2,
    LOG_10 = 3,
    SIN = 4,
    COS = 5,
    TAN = 6,
    CSC = 7,
    SEC = 8,
    COT = 9,
    ASIN = 10,
    ACOS = 11,
    ATAN = 12,
    ACSC = 13,
    ASEC = 14,
    ACOT = 15,
    SINH = 16,
    COSH = 17,
    TANH = 18,
    COTH = 19,
    SECH = 20,
    CSCH = 21,
    ASINH = 22,
    ACOSH = 23,
    ATANH = 24,
    ACOTH = 25,
    ACSCH = 26,
    ASECH = 27
  };
  Function();
  Function(FunctionNames func);
  Function(std::string func);
  Function(const Function& copy);
  virtual ~Function();

  virtual std::shared_ptr<ExpressionBase> eval();

  virtual std::string Latex(bool recurse = true) const;
  // virtual std::string Tree(std::size_t indent = 2) const;

  operator std::shared_ptr<FunctionBase>();
  operator std::shared_ptr<ExpressionBase>();

  FunctionNames func_;
};
}  // namespace radix

#endif  // RADIX_FUNCTION_FUNCTION_HPP_
