#ifndef RADIX_FUNCTION_FUNCTION_HPP_
#define RADIX_FUNCTION_FUNCTION_HPP_

#include <memory>
#include <ostream>
#include <map>
#include <string>

#include "function_base.hpp"
#include "../utility.hpp"

namespace radix {
enum FunctionNames {
  ABS,
  MAX,
  MIN,
  EXP,
  EXP2,
  EXP10,
  LOG,
  LOG2,
  LOG10,
  POW,
  SQRT,
  CBRT,
  ROOT,
  HYPOT,
  COS,
  SIN,
  TAN,
  SEC,
  CSC,
  COT,
  ACOS,
  ASIN,
  ATAN,
  ACSC,
  ASEC,
  ACOT,
  SINH,
  COSH,
  TANH,
  COTH,
  SECH,
  CSCH,
  ASINH,
  ACOSH,
  ATANH,
  ACOTH,
  ACSCH,
  ASECH,
  ERF,
  ERFC,
  TGAMMA,
  LGAMMA,
  CEIL,
  FLOOR,
  TRUNC,
  ROUND
};
extern std::map<FunctionNames, quad<std::string, std::size_t, std::string, std::string>> fmap;
class Function : public FunctionBase {
 public:
  Function();
  Function(FunctionNames func);
  Function(std::string func);
  Function(const Function& copy);
  virtual ~Function();

  virtual std::shared_ptr<ExpressionBase> Eval(
      std::shared_ptr<ExpressionBase> a);
  virtual std::shared_ptr<ExpressionBase> Eval(
      std::shared_ptr<ExpressionBase> a, std::shared_ptr<ExpressionBase> b);

  virtual std::string Unicode(bool recurse = true) const;
  virtual std::string Latex(bool recurse = true) const;
  // virtual std::string Tree(std::size_t indent = 2) const;

  operator std::shared_ptr<FunctionBase>();
  operator std::shared_ptr<ExpressionBase>();

  FunctionNames func_;
  std::size_t nargs_;
};
}  // namespace radix

#endif  // RADIX_FUNCTION_FUNCTION_HPP_
