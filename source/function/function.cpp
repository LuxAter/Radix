#include "function/function.hpp"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "function/function_base.hpp"
#include "value/value.hpp"

radix::Function::Function() : FunctionBase(STANDARD), func_(NONE) {}
radix::Function::Function(FunctionNames func)
    : FunctionBase(STANDARD), func_(func) {}
radix::Function::Function(std::string func) : FunctionBase(STANDARD) {
  std::transform(func.begin(), func.end(), func.begin(), ::tolower);
  if (func == "log2") {
    func_ = LOG_2;
    nargs_ = 1;
  } else if (func == "log") {
    func_ = LOG;
    nargs_ = 1;
  } else if (func == "log10") {
    func_ = LOG_10;
    nargs_ = 1;
  } else if (func == "sin") {
    func_ = SIN;
    nargs_ = 1;
  } else if (func == "cos") {
    func_ = COS;
    nargs_ = 1;
  } else if (func == "tan") {
    func_ = TAN;
    nargs_ = 1;
  } else if (func == "csc") {
    func_ = CSC;
    nargs_ = 1;
  } else if (func == "sec") {
    func_ = SEC;
    nargs_ = 1;
  } else if (func == "cot") {
    func_ = COT;
    nargs_ = 1;
  } else if (func == "asin") {
    func_ = ASIN;
    nargs_ = 1;
  } else if (func == "acos") {
    func_ = ACOS;
    nargs_ = 1;
  } else if (func == "atan") {
    func_ = ATAN;
    nargs_ = 1;
  } else if (func == "acsc") {
    func_ = ACSC;
    nargs_ = 1;
  } else if (func == "asec") {
    func_ = ASEC;
    nargs_ = 1;
  } else if (func == "acot") {
    func_ = ACOT;
    nargs_ = 1;
  } else if (func == "sinh") {
    func_ = SINH;
    nargs_ = 1;
  } else if (func == "cosh") {
    func_ = COSH;
    nargs_ = 1;
  } else if (func == "tanh") {
    func_ = TANH;
    nargs_ = 1;
  } else if (func == "coth") {
    func_ = COTH;
    nargs_ = 1;
  } else if (func == "sech") {
    func_ = SECH;
    nargs_ = 1;
  } else if (func == "csch") {
    func_ = CSCH;
    nargs_ = 1;
  } else if (func == "asinh") {
    func_ = ASINH;
    nargs_ = 1;
  } else if (func == "acosh") {
    func_ = ACOSH;
    nargs_ = 1;
  } else if (func == "atanh") {
    func_ = ATANH;
    nargs_ = 1;
  } else if (func == "acoth") {
    func_ = ACOTH;
    nargs_ = 1;
  } else if (func == "acsch") {
    func_ = ACSCH;
    nargs_ = 1;
  } else if (func == "asech") {
    func_ = ASECH;
    nargs_ = 1;
  }
}
radix::Function::Function(const Function& copy)
    : FunctionBase(STANDARD), func_(copy.func_) {}

radix::Function::~Function() {}

std::shared_ptr<radix::ExpressionBase> radix::Function::eval() {
  // switch(func_){
  //   case SIN:
  //     return
  //     std::dynamic_pointer_cast<ExpressionBase>(sin(std::dynamic_pointer_cast<Value>(children_.front())));
  // }
}

std::string radix::Function::Unicode(bool recurse) const {
  std::vector<std::string> args;
  if (recurse) {
    for (std::size_t i = 0; i < nargs_ + 1; i++) {
      args.push_back("$" + std::to_string(i));
    }
  } else {
    for (std::size_t i = 0; i < nargs_ + 1; i++) {
      args.push_back("");
    }
  }
  switch(func_){
    case LOG_2:
      return "log2(" + args.at(0) + ")";
    case LOG:
      return "log(" + args.at(0) + ")";
    case LOG_10:
      return "log10(" + args.at(0) + ")";
    case SIN:
      return "sin(" + args.at(0) + ")";
    case COS:
      return "cos(" + args.at(0) + ")";
    case TAN:
      return "tan(" + args.at(0) + ")";
    case CSC:
      return "csc(" + args.at(0) + ")";
    case SEC:
      return "sec(" + args.at(0) + ")";
    case COT:
      return "cot(" + args.at(0) + ")";
    case ASIN:
      return "asin(" + args.at(0) + ")";
    case ACOS:
      return "acos(" + args.at(0) + ")";
    case ATAN:
      return "atan(" + args.at(0) + ")";
    case ACSC:
      return "acsc(" + args.at(0) + ")";
    case ASEC:
      return "asec(" + args.at(0) + ")";
    case ACOT:
      return "acot(" + args.at(0) + ")";
    case SINH:
      return "sinh(" + args.at(0) + ")";
    case COSH:
      return "cosh(" + args.at(0) + ")";
    case TANH:
      return "tanh(" + args.at(0) + ")";
    case CSCH:
      return "csch(" + args.at(0) + ")";
    case SECH:
      return "sech(" + args.at(0) + ")";
    case COTH:
      return "coth(" + args.at(0) + ")";
    case ASINH:
      return "asinh(" + args.at(0) + ")";
    case ACOSH:
      return "acosh(" + args.at(0) + ")";
    case ATANH:
      return "atanh(" + args.at(0) + ")";
    case ACSCH:
      return "acsch(" + args.at(0) + ")";
    case ASECH:
      return "asech(" + args.at(0) + ")";
    case ACOTH:
      return "acoth(" + args.at(0) + ")";
  }
}
std::string radix::Function::Latex(bool recurse) const {
  std::vector<std::string> args;
  if (recurse) {
    for (std::size_t i = 0; i < nargs_ + 1; i++) {
      args.push_back("$" + std::to_string(i));
    }
  } else {
    for (std::size_t i = 0; i < nargs_ + 1; i++) {
      args.push_back("");
    }
  }
  switch (func_) {
    case LOG_2:
      return "\\log_{2}\\left(" + args.at(0) + "\\right)";
    case LOG:
      if (args.size() == 1) {
        return "\\log\\left(" + args.at(0) + "\\right)";
      } else {
        return "\\log_{" + args.at(0) + "}\\left(" + args.back() + "\\right)";
      }
    case LOG_10:
      return "\\log_{10}\\left(" + args.at(0) + "\\right)";
    case SIN:
      return "\\sin\\left(" + args.at(0) + "\\right)";
    case COS:
      return "\\cos\\left(" + args.at(0) + "\\right)";
    case TAN:
      return "\\tan\\left(" + args.at(0) + "\\right)";
    case CSC:
      return "\\csc\\left(" + args.at(0) + "\\right)";
    case SEC:
      return "\\sec\\left(" + args.at(0) + "\\right)";
    case COT:
      return "\\cot\\left(" + args.at(0) + "\\right)";
    case ASIN:
      return "\\arcsin\\left(" + args.at(0) + "\\right)";
    case ACOS:
      return "\\arccos\\left(" + args.at(0) + "\\right)";
    case ATAN:
      return "\\arctan\\left(" + args.at(0) + "\\right)";
    case ACSC:
      return "\\text{arccsc}\\left(" + args.at(0) + "\\right)";
    case ASEC:
      return "\\text{arcsec}\\left(" + args.at(0) + "\\right)";
    case ACOT:
      return "\\text{arccot}\\left(" + args.at(0) + "\\right)";
    case SINH:
      return "\\sinh\\left(" + args.at(0) + "\\right)";
    case COSH:
      return "\\cosh\\left(" + args.at(0) + "\\right)";
    case TANH:
      return "\\tanh\\left(" + args.at(0) + "\\right)";
    case COTH:
      return "\\text{coth}\\left(" + args.at(0) + "\\right)";
    case SECH:
      return "\\text{sech}\\left(" + args.at(0) + "\\right)";
    case CSCH:
      return "\\text{csch}\\left(" + args.at(0) + "\\right)";
    case ASINH:
      return "\\text{arcsinh}\\left(" + args.at(0) + "\\right)";
    case ACOSH:
      return "\\text{arccosh}\\left(" + args.at(0) + "\\right)";
    case ATANH:
      return "\\text{arctanh}\\left(" + args.at(0) + "\\right)";
    case ACOTH:
      return "\\text{arccoth}\\left(" + args.at(0) + "\\right)";
    case ASECH:
      return "\\text{arcsech}\\left(" + args.at(0) + "\\right)";
    case ACSCH:
      return "\\text{arccsch}\\left(" + args.at(0) + "\\right)";
  }
  return std::string();
}

radix::Function::operator std::shared_ptr<radix::FunctionBase>() {
  return std::dynamic_pointer_cast<radix::FunctionBase>(
      std::make_shared<Function>(*this));
}
radix::Function::operator std::shared_ptr<radix::ExpressionBase>() {
  return std::dynamic_pointer_cast<radix::ExpressionBase>(
      std::make_shared<Function>(*this));
}
