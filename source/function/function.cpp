#include "function/function.hpp"

#include <memory>
#include <ostream>

#include "expression.hpp"

radix::Function::Function() : Expression(FUNCTION), type_(USER) {}
radix::Function::Function(FunctionType type): Expression(FUNCTION), type_(type){}
radix::Function::~Function(){}

std::string radix::Function::Latex() const {
  return std::string();
}
std::string radix::Function::Tree(std::size_t indent) const {
  std::string ret = "Exp[Function[NULL]]()";
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

std::ostream& radix::operator<<(std::ostream& out, const std::shared_ptr<Function>& lhs){
  if(lhs == NULL){
    out << "(null)";
    return out;
  }
  switch(lhs->type_){
    case OPERATOR: {
                     // out << *std::dynamic_pointer_cast<Operator>(lhs);
                     break;
                   }
    case STANDARD: {
                     // out << *std::dynamic_pointer_cast<Standard>(lhs);
                     break;
                   }
    case USER: {
                     // out << *std::dynamic_pointer_cast<User>(lhs);
                     break;
                   }
  };
  return out;
}
