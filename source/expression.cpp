#include "expression.hpp"

#include <iostream>

radix::Expression::Expression() {}
radix::Expression::Expression(const ExpressionType& type) : type_(type) {}
radix::Expression::~Expression() {}

std::string radix::Expression::Latex() const { return std::string(); }
std::string radix::Expression::Tree(std::size_t indent) const {
  std::string ret = "Exp[NULL]()";
  std::string rep = "\u2502" + std::string(indent, ' ');
  std::string bar;
  for(std::size_t i = 0; i < indent; i++){
    bar += "\u2500";
  }
  if(children_.size() != 0){
    ret += "\n";
  }
  for (auto it = children_.begin(); it != children_.end(); ++it) {
    if(it != children_.end() - 1){
      ret += "\u251c" + bar;
    }else{
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
    if(it != children_.end() - 1){
      ret += "\n";
    }
  }
  return ret;
}

std::shared_ptr<radix::Expression> radix::GenerateExpression(std::string_view) {
  return std::make_shared<Expression>(Expression());
}
