#include "function/operator.hpp"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>

#include "function/function_base.hpp"
#include "value/value.hpp"

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
    } else if (op == "sub") {
      op_ = SUB;
    } else if (op == "mul") {
      op_ = MUL;
    } else if (op == "div") {
      op_ = DIV;
    } else if (op == "mod") {
      op_ = MOD;
    } else if (op == "pow") {
      op_ = POW;
    } else if (op == "fac") {
      op_ = FAC;
    }
  }
}
radix::Operator::Operator(const Operator& copy)
    : FunctionBase(OPERATOR), op_(copy.op_) {}

radix::Operator::~Operator() {}

std::string radix::Operator::Latex(bool recurse) const {
  if (recurse) {
    switch (op_) {
      case ADD:
        return "$0+$1";
      case SUB:
        return "$0-$1";
      case MUL:
        return "$0*$1";
      case DIV:
        return "$0/$1";
      case MOD:
        return "$0%$1";
      case POW:
        return "$0^$1";
      case FAC:
        return "$0!";
    }
  } else {
    switch (op_) {
      case ADD:
        return "+";
      case SUB:
        return "-";
      case MUL:
        return "*";
      case DIV:
        return "/";
      case MOD:
        return "%";
      case POW:
        return "^";
      case FAC:
        return "!";
    }
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
      break;
    }
    case '-': {
      op_ = SUB;
      break;
    }
    case '*': {
      op_ = MUL;
      break;
    }
    case '&': {
      op_ = MUL;
      break;
    }
    case '/': {
      op_ = DIV;
      break;
    }
    case '%': {
      op_ = MOD;
      break;
    }
    case '^': {
      op_ = POW;
      break;
    }
    case '!': {
      op_ = FAC;
      break;
    }
  };
}
