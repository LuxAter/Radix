#include "function/operator.hpp"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "function/function_base.hpp"
#include "value/long.hpp"
#include "value/value.hpp"


#include <iostream>

radix::Operator::Operator() : FunctionBase(OPERATOR), op_(NONE) {}
radix::Operator::Operator(OperatorOp op) : FunctionBase(OPERATOR), op_(op) {}
radix::Operator::Operator(char op) : FunctionBase(OPERATOR) { ParseChar(op); }
radix::Operator::Operator(std::string op) : FunctionBase(OPERATOR) {
  if (op.size() == 1) {
    ParseChar(op[0]);
  } else {
    std::transform(op.begin(), op.end(), op.begin(), ::tolower);
    if (op == "add") {
      op_ = ADD;
      nargs_ = 2;
    } else if (op == "sub") {
      op_ = SUB;
      nargs_ = 2;
    } else if (op == "mul") {
      op_ = MUL;
      nargs_ = 2;
    } else if (op == "div") {
      op_ = DIV;
      nargs_ = 2;
    } else if (op == "mod") {
      op_ = MOD;
      nargs_ = 2;
    } else if (op == "pow") {
      op_ = POW;
      nargs_ = 2;
    } else if (op == "fac") {
      op_ = FAC;
      nargs_ = 1;
    }
  }
}
radix::Operator::Operator(const Operator& copy)
    : FunctionBase(OPERATOR), op_(copy.op_), nargs_(copy.nargs_) {}

radix::Operator::~Operator() {}

std::shared_ptr<radix::ExpressionBase> radix::Operator::Eval(
    std::shared_ptr<ExpressionBase> a, std::shared_ptr<ExpressionBase> b) {
  std::shared_ptr<radix::Value> lhs =
      std::dynamic_pointer_cast<radix::Value>(a);
  std::shared_ptr<radix::Value> rhs =
      std::dynamic_pointer_cast<radix::Value>(b);
  switch (op_) {
    case ADD:
      return (lhs + rhs);
    case SUB:
      return (lhs - rhs);
    case MUL:
      return (lhs * rhs);
    case DIV:
      return (lhs / rhs);
    case MOD:
      return (lhs % rhs);
    case POW:
      return pow(lhs, rhs);
  }

  return nullptr;
}

std::string radix::Operator::Unicode(bool recurse) const {
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
  switch (op_) {
    case ADD:
      return args.at(0) + "+" + args.at(1);
    case SUB:
      return args.at(0) + "-" + args.at(1);
    case MUL:
      return args.at(0) + "*" + args.at(1);
    case DIV:
      return args.at(0) + "/" + args.at(1);
    case MOD:
      return args.at(0) + "%" + args.at(1);
    case POW:
      return args.at(0) + "^" + args.at(1);
    case FAC:
      return args.at(0) + "!";
  }
}
std::string radix::Operator::Latex(bool recurse) const {
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
  switch (op_) {
    case ADD:
      return args.at(0) + "+" + args.at(1);
    case SUB:
      return args.at(0) + "-" + args.at(1);
    case MUL:
      return args.at(0) + " \\cdot " + args.at(1);
    case DIV:
      return "\\frac{" + args.at(0) + "}{" + args.at(1) + "}";
    case MOD:
      return args.at(0) + "%" + args.at(1);
    case POW:
      return "{" + args.at(0) + "}^{" + args.at(1) + "}";
    case FAC:
      return args.at(0) + "!";
  }
  return std::string();
}
radix::Operator::operator std::shared_ptr<radix::FunctionBase>() {
  return std::dynamic_pointer_cast<radix::FunctionBase>(
      std::make_shared<Operator>(*this));
}
radix::Operator::operator std::shared_ptr<radix::ExpressionBase>() {
  return std::dynamic_pointer_cast<radix::ExpressionBase>(
      std::make_shared<Operator>(*this));
}

void radix::Operator::ParseChar(char op) {
  switch (op) {
    case '+': {
      op_ = ADD;
      nargs_ = 2;
      break;
    }
    case '-': {
      op_ = SUB;
      nargs_ = 2;
      break;
    }
    case '*': {
      op_ = MUL;
      nargs_ = 2;
      break;
    }
    case '&': {
      op_ = MUL;
      nargs_ = 2;
      break;
    }
    case '/': {
      op_ = DIV;
      nargs_ = 2;
      break;
    }
    case '%': {
      op_ = MOD;
      nargs_ = 2;
      break;
    }
    case '^': {
      op_ = POW;
      nargs_ = 2;
      break;
    }
    case '!': {
      op_ = FAC;
      nargs_ = 1;
      break;
    }
  };
}
