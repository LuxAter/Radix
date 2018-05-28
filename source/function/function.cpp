#include "function/function.hpp"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>

#include "function/function_base.hpp"
#include "value/value.hpp"

radix::Function::Function() : FunctionBase(STANDARD), func_(NONE) {}
radix::Function::Function(FunctionNames func)
    : FunctionBase(STANDARD), func_(func) {}
radix::Function::Function(std::string func) : FunctionBase(STANDARD) {
  std::transform(func.begin(), func.end(), func.begin(), ::tolower);
  if(func == "log2"){
    func_ = LOG_2;
  }else if(func == "log"){
    func_ = LOG;
  }else if(func == "log10"){
    func_ = LOG_10;
  }else if(func == "sin"){
    func_ = SIN;
  }else if(func == "cos"){
    func_ = COS;
  }else if(func == "tan"){
    func_ = TAN;
  }else if(func == "csc"){
    func_ = CSC;
  }else if(func == "sec"){
    func_ = SEC;
  }else if(func == "cot"){
    func_ = COT;
  }else if(func == "asin"){
    func_ = ASIN;
  }else if(func == "acos"){
    func_ = ACOS;
  }else if(func == "atan"){
    func_ = ATAN;
  }else if(func == "acsc"){
    func_ = ACSC;
  }else if(func == "asec"){
    func_ = ASEC;
  }else if(func == "acot"){
    func_ = ACOT;
  }else if(func == "sinh"){
    func_ = SINH;
  }else if(func == "cosh"){
    func_ = COSH;
  }else if(func == "tanh"){
    func_ = TANH;
  }else if(func == "coth"){
    func_ = COTH;
  }else if(func == "sech"){
    func_ = SECH;
  }else if(func == "csch"){
    func_ = CSCH;
  }else if(func == "asinh"){
    func_ = ASINH;
  }else if(func == "acosh"){
    func_ = ACOSH;
  }else if(func == "atanh"){
    func_ = ATANH;
  }else if(func == "acoth"){
    func_ = ACOTH;
  }else if(func == "acsch"){
    func_ = ACSCH;
  }else if(func == "asech"){
    func_ = ASECH;
  }
}
radix::Function::Function(const Function& copy)
    : FunctionBase(STANDARD), func_(copy.func_) {}

radix::Function::~Function() {}

std::shared_ptr<radix::ExpressionBase> radix::Function::eval(){
  // switch(func_){
  //   case SIN:
  //     return std::dynamic_pointer_cast<ExpressionBase>(sin(std::dynamic_pointer_cast<Value>(children_.front())));
  // }
}

std::string radix::Function::Latex(bool recurse) const {
  // std::vector<std::string> children;
  // if (recurse == true) {
  //   for (auto& it : children_) {
  //     children.push_back(it->Latex());
  //   }
  // } else {
  //   children.push_back(std::string());
  // }
  // switch (func_) {
  //   case LOG_2:
  //     return "\\log_{2}\\left(" + children.front() + "\\right)";
  //   case LOG:
  //     if (children.size() == 1) {
  //       return "\\log\\left(" + children.front() + "\\right)";
  //     } else {
  //       return "\\log_{" + children.front() + "}\\left(" + children.back() +
  //              "\\right)";
  //     }
  //   case LOG_10:
  //     return "\\log_{10}\\left(" + children.front() + "\\right)";
  //   case SIN:
  //     return "\\sin\\left(" + children.front() + "\\right)";
  //   case COS:
  //     return "\\cos\\left(" + children.front() + "\\right)";
  //   case TAN:
  //     return "\\tan\\left(" + children.front() + "\\right)";
  //   case CSC:
  //     return "\\csc\\left(" + children.front() + "\\right)";
  //   case SEC:
  //     return "\\sec\\left(" + children.front() + "\\right)";
  //   case COT:
  //     return "\\cot\\left(" + children.front() + "\\right)";
  //   case ASIN:
  //     return "\\arcsin\\left(" + children.front() + "\\right)";
  //   case ACOS:
  //     return "\\arccos\\left(" + children.front() + "\\right)";
  //   case ATAN:
  //     return "\\arctan\\left(" + children.front() + "\\right)";
  //   case ACSC:
  //     return "\\text{arccsc}\\left(" + children.front() + "\\right)";
  //   case ASEC:
  //     return "\\text{arcsec}\\left(" + children.front() + "\\right)";
  //   case ACOT:
  //     return "\\text{arccot}\\left(" + children.front() + "\\right)";
  //   case SINH:
  //     return "\\sinh\\left(" + children.front() + "\\right)";
  //   case COSH:
  //     return "\\cosh\\left(" + children.front() + "\\right)";
  //   case TANH:
  //     return "\\tanh\\left(" + children.front() + "\\right)";
  //   case COTH:
  //     return "\\text{coth}\\left(" + children.front() + "\\right)";
  //   case SECH:
  //     return "\\text{sech}\\left(" + children.front() + "\\right)";
  //   case CSCH:
  //     return "\\text{csch}\\left(" + children.front() + "\\right)";
  //   case ASINH:
  //     return "\\text{arcsinh}\\left(" + children.front() + "\\right)";
  //   case ACOSH:
  //     return "\\text{arccosh}\\left(" + children.front() + "\\right)";
  //   case ATANH:
  //     return "\\text{arctanh}\\left(" + children.front() + "\\right)";
  //   case ACOTH:
  //     return "\\text{arccoth}\\left(" + children.front() + "\\right)";
  //   case ASECH:
  //     return "\\text{arcsech}\\left(" + children.front() + "\\right)";
  //   case ACSCH:
  //     return "\\text{arccsch}\\left(" + children.front() + "\\right)";
  // }
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
