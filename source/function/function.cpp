#include "function/function.hpp"

#include <algorithm>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "function/function_base.hpp"
#include "utility.hpp"
#include "value/value.hpp"
#include "value/long.hpp"

#include <iostream>

namespace radix {
std::map<FunctionNames,
                quad<std::string, std::size_t, std::string, std::string>>
    fmap{{ABS, {"abs", 1, "|$0|", "\\lvert $0\\rvert"}},
         {MAX, {"max", 2, "max($0,$1)", "\\text{max}\\left($0,$1\\right)"}},
         {MIN, {"min", 2, "min($0,$1)", "\\text{min}\\left($0,$1\\right)"}},
         {EXP, {"exp", 1, "e^($0)", "e^{$0}"}},
         {EXP2, {"exp2", 1, "2^($0)", "2^{$0}"}},
         {EXP10, {"exp10", 1, "10^($0)", "10^{$0}"}},
         {LOG, {"log", 1, "log($0)", "\\log\\left($0\\right)"}},
         {LOG2, {"log2", 1, "log2($0)", "\\log_{2}\\left($0\\right)"}},
         {LOG10, {"log10", 1, "log10($0)", "\\log_{10}\\left($0\\right)"}},
         {POW, {"pow", 2, "($0)^($1)", "{\\left($0\\right)}^{$1}"}},
         {SQRT, {"sqrt", 1, "sqrt($0)", "\\sqrt{$0}"}},
         {CBRT, {"cbrt", 1, "cbrt($0)", "\\sqrt[3]{$0}"}},
         {ROOT, {"root", 2, "($1)^(1/($0))", "\\sqrt[$0]{$1}"}},
         {HYPOT,
          {"hypot", 2, "hypot($0,$1)", "\\text{hypot}\\left($0,$1\\right)"}},
         {SIN, {"sin", 1, "sin($0)", "\\sin\\left($0\\right)"}},
         {COS, {"cos", 1, "cos($0)", "\\cos\\left($0\\right)"}},
         {TAN, {"tan", 1, "tan($0)", "\\tan\\left($0\\right)"}},
         {SEC, {"sec", 1, "sec($0)", "\\sec\\left($0\\right)"}},
         {CSC, {"csc", 1, "csc($0)", "\\csc\\left($0\\right)"}},
         {COT, {"cot", 1, "cot($0)", "\\cot\\left($0\\right)"}},
         {ACOS, {"acos", 1, "acos($0)", "\\arccos\\left($0\\right)"}},
         {ASIN, {"asin", 1, "asin($0)", "\\arcsin\\left($0\\right)"}},
         {ATAN, {"atan", 1, "atan($0)", "\\arctan\\left($0\\right)"}},
         {ASEC, {"asec", 1, "asec($0)", "\\text{arcsec}\\left($0\\right)"}},
         {ACSC, {"acsc", 1, "acsc($0)", "\\text{arccsc}\\left($0\\right)"}},
         {ACOT, {"acot", 1, "acot($0)", "\\text{arccot}\\left($0\\right)"}},
         {SINH, {"sinh", 1, "sinh($0)", "\\sinh\\left($0\\right)"}},
         {COSH, {"cosh", 1, "cosh($0)", "\\cosh\\left($0\\right)"}},
         {TANH, {"tanh", 1, "tanh($0)", "\\tanh\\left($0\\right)"}},
         {SECH, {"sech", 1, "sech($0)", "\\text{sech}\\left($0\\right)"}},
         {CSCH, {"csch", 1, "csch($0)", "\\text{csch}\\left($0\\right)"}},
         {COTH, {"coth", 1, "coth($0)", "\\text{coth}\\left($0\\right)"}},
         {ASINH, {"asinh", 1, "asinh($0)", "\\text{arcsinh}\\left($0\\right)"}},
         {ACOSH, {"acosh", 1, "acosh($0)", "\\text{arccosh}\\left($0\\right)"}},
         {ATANH, {"atanh", 1, "atanh($0)", "\\text{arctanh}\\left($0\\right)"}},
         {ASECH, {"asech", 1, "asech($0)", "\\text{arcsech}\\left($0\\right)"}},
         {ACSCH, {"acsch", 1, "acsch($0)", "\\text{arccsch}\\left($0\\right)"}},
         {ACOTH, {"acoth", 1, "acoth($0)", "\\text{arccoth}\\left($0\\right)"}},
         {ERF, {"erf", 1, "erf($0)", "\\erf\\left($0\\right)"}},
         {ERFC, {"erfc", 1, "erfc($0)", "\\erfc\\left($0\\right)"}},
         {TGAMMA, {"tgamma", 1, "gamma($0)", "\\Gamma\\left($0\\right)"}},
         {LGAMMA,
          {"lgamma", 1, "lgamma($0)",
           "\\log\\lvert\\Gamma\\left($0\\right)\\rvert"}},
         {CEIL, {"ceil", 1, "ceil($0)", "\\left\\lceil$0\\right\\rceil"}},
         {FLOOR, {"floor", 1, "floor($0)", "\\left\\lfloor$0\\right\\rfloor"}},
         {TRUNC, {"trunc", 1, "trunc($0)", "\\text{trunc}\\left($0\\right)"}},
         {ROUND, {"round", 1, "round($0)", "\\text{round}\\left($0\\right)"}}};
}  // namespace radix

radix::Function::Function() : FunctionBase(FUNCTION) {}
radix::Function::Function(FunctionNames func)
    : FunctionBase(FUNCTION), func_(func) {}
radix::Function::Function(std::string func) : FunctionBase(FUNCTION) {
  std::transform(func.begin(), func.end(), func.begin(), ::tolower);
  for (auto it : fmap) {
    if (it.second.first == func) {
      func_ = it.first;
      nargs_ = it.second.second;
    }
  }
}
radix::Function::Function(const Function& copy)
    : FunctionBase(FUNCTION), func_(copy.func_), nargs_(copy.nargs_) {}

radix::Function::~Function() {}

std::shared_ptr<radix::ExpressionBase> radix::Function::Eval(
    std::shared_ptr<ExpressionBase> a) {
  std::shared_ptr<radix::Value> lhs =
      std::dynamic_pointer_cast<radix::Value>(a);
  switch (func_) {
    case ABS:
      return abs(lhs);
    case EXP:
      return exp(lhs);
    case EXP2:
      return exp2(lhs);
    case EXP10:
      return exp10(lhs);
    case LOG:
      return log(lhs);
    case LOG2:
      return log2(lhs);
    case LOG10:
      return log10(lhs);
    case SQRT:
      return sqrt(lhs);
    case CBRT:
      return cbrt(lhs);
    case SIN:
      return sin(lhs);
    case COS:
      return cos(lhs);
    case TAN:
      return tan(lhs);
    case SEC:
      return sec(lhs);
    case CSC:
      return csc(lhs);
    case COT:
      return cot(lhs);
    case ASIN:
      return asin(lhs);
    case ACOS:
      return acos(lhs);
    case ATAN:
      return atan(lhs);
    case ASEC:
      return acos(Long(1) / lhs);
    case ACSC:
      return asin(Long(1) / lhs);
    case ACOT:
      return atan(Long(1) / lhs);
    case SINH:
      return sinh(lhs);
    case COSH:
      return cosh(lhs);
    case TANH:
      return tanh(lhs);
    case SECH:
      return sech(lhs);
    case CSCH:
      return csch(lhs);
    case COTH:
      return coth(lhs);
    case ASINH:
      return asinh(lhs);
    case ACOSH:
      return acosh(lhs);
    case ATANH:
      return atanh(lhs);
    case ASECH:
      return acosh(Long(1) / lhs);
    case ACSCH:
      return asinh(Long(1) / lhs);
    case ACOTH:
      return atanh(Long(1) / lhs);
    case ERF:
      return erf(lhs);
    case ERFC:
      return erfc(lhs);
    case TGAMMA:
      return tgamma(lhs);
    case LGAMMA:
      return lgamma(lhs);
    case CEIL:
      return ceil(lhs);
    case FLOOR:
      return floor(lhs);
    case TRUNC:
      return trunc(lhs);
    case ROUND:
      return round(lhs);
    default:
      return nullptr;
  }
}

std::shared_ptr<radix::ExpressionBase> radix::Function::Eval(
    std::shared_ptr<ExpressionBase> a, std::shared_ptr<ExpressionBase> b) {
  std::shared_ptr<radix::Value> lhs =
                                    std::dynamic_pointer_cast<radix::Value>(a),
                                rhs =
                                    std::dynamic_pointer_cast<radix::Value>(b);
  switch (func_) {
    case MAX:
      return max(lhs, rhs);
    case MIN:
      return min(lhs, rhs);
    default:
      return nullptr;
  }
}

std::string radix::Function::Unicode(bool recurse) const {
  std::string ret = fmap.at(func_).third;
  if (!recurse) {
    for (std::size_t i = 0; i < nargs_; ++i) {
      std::size_t pos = 0;
      std::string find_str = "$" + std::to_string(i);
      while ((pos = ret.find(find_str, pos)) != std::string::npos) {
        ret.replace(pos, find_str.length(), "");
      }
    }
  }
  return ret;
}

std::string radix::Function::Latex(bool recurse) const {
  std::string ret = fmap.at(func_).fourth;
  if (!recurse) {
    for (std::size_t i = 0; i < nargs_; ++i) {
      std::size_t pos = 0;
      std::string find_str = "$" + std::to_string(i);
      while ((pos = ret.find(find_str, pos)) != std::string::npos) {
        ret.replace(pos, find_str.length(), "");
      }
    }
  }
  return ret;
}

radix::Function::operator std::shared_ptr<radix::FunctionBase>() {
  return std::dynamic_pointer_cast<radix::FunctionBase>(
      std::make_shared<Function>(*this));
}
radix::Function::operator std::shared_ptr<radix::ExpressionBase>() {
  return std::dynamic_pointer_cast<radix::ExpressionBase>(
      std::make_shared<Function>(*this));
}
