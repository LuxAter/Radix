#include "function/operator.hpp"

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>

#include "function/function_base.hpp"

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
  std::vector<std::string> children;
  if (recurse == true) {
    for (auto& it : children_) {
      children.push_back(it->Latex());
    }
  } else {
    children.push_back(std::string());
  }
  switch (op_) {
    case ADD:
      return children.front() + "+" + children.back();
    case SUB:
      return children.front() + "-" + children.back();
    case MUL:
      return children.front() + "\\cdot" + children.back();
    case DIV:
      return "\\frac{" + children.front() + "}{" + children.back() + "}";
    case MOD:
      return children.front() + "\\bmod" + children.back();
    case POW:
      return "{" + children.front() + "}^{" + children.back() + "}";
    case FAC:
      return children.front() + "!";
  }
  return std::string();
}
std::string radix::Operator::Tree(std::size_t indent) const {
  std::string ret = "Exp[Function[Operator]](" + Latex(false) + ")";
  std::string rep = "\u2502" + std::string(indent, ' ');
  std::string bar;
  for (std::size_t i = 0; i < indent; i++) {
    bar += "\u2500";
  }
  if (children_.size() != 0) {
    ret += "\n";
  }
  for (auto it = children_.begin(); it != children_.end(); ++it) {
    if (it != children_.end() - 1) {
      ret += "\u251c" + bar;
    } else {
      ret += "\u2514" + bar;
      rep = std::string(indent + 1, ' ');
    }
    std::string sub = (*it)->Tree(indent);
    size_t pos = 0;
    while ((pos = sub.find('\n', pos)) != std::string::npos) {
      sub.insert(++pos, rep);
      pos += rep.length();
    }
    ret += sub;
    if (it != children_.end() - 1) {
      ret += "\n";
    }
  }
  return ret;
}

radix::Operator::operator std::shared_ptr<radix::FunctionBase>() {
  return std::dynamic_pointer_cast<radix::FunctionBase>(
      std::make_shared<Operator>(*this));
}
radix::Operator::operator std::shared_ptr<radix::Expression>() {
  return std::dynamic_pointer_cast<radix::Expression>(
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
