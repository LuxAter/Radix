#include "expression.hpp"

#include <iostream>

#include "function/function_base.hpp"
#include "value/long.hpp"
#include "value/value.hpp"
#include "value/variable.hpp"

radix::Expression::Expression() {}
radix::Expression::Expression(const ExpressionType& type) : type_(type) {}
radix::Expression::Expression(const Expression& copy)
    : type_(copy.type_),
      next_(copy.next_),
      prev_(copy.prev_),
      children_(copy.children_) {}
radix::Expression::~Expression() {}

void radix::Expression::SetVariable(std::string ref,
                                    std::shared_ptr<Expression> val) {
  for (auto& it : children_) {
    it->SetVariable(ref, val);
    if (it->type_ == VALUE) {
      std::shared_ptr<Value> vp = std::dynamic_pointer_cast<Value>(it);
      if (vp->type_ == VARIABLE) {
        std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(it);
        if (var->GetRef() == ref) {
          var->SetVal(std::dynamic_pointer_cast<Value>(val));
        }
      }
    }
  }
}
void radix::Expression::SetVariable(std::shared_ptr<Expression> val) {
  if (val->type_ != VALUE) {
    return;
  } else if (std::dynamic_pointer_cast<Value>(val)->type_ != VARIABLE) {
    return;
  }
  for (auto& it : children_) {
    it->SetVariable(val);
    if (it->type_ == VALUE) {
      std::shared_ptr<Value> vp = std::dynamic_pointer_cast<Value>(it);
      if (vp->type_ == VARIABLE) {
        std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(it);
        if (var->GetRef() ==
            std::dynamic_pointer_cast<Variable>(val)->GetRef()) {
          var->SetVal(std::dynamic_pointer_cast<Variable>(val)->GetVal());
        }
      }
    }
  }
}

// std::shared_ptr<radix::Expression> radix::Expression::Eval() const {
//   std::cout << "EVALUATING...\n";
//   std::shared_ptr<Expression> exp =
//       CopyExpression(this);
//   // exp->SetVariable("x", Long(2018));
//   if(exp->HasOnlyLeafs()){
//   }
//   std::cout << exp->Tree() << "\n";
//   return exp;
//   return NULL;
// }

std::string radix::Expression::Latex(bool recurse) const {
  return std::string();
}
std::string radix::Expression::Tree(std::size_t indent) const {
  std::string ret = "Exp[NULL]()";
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

void radix::Expression::insert(std::size_t pos,
                               std::shared_ptr<Expression> child) {
  children_.insert(children_.begin() + pos, child);
  if (*(children_.begin()) != child) {
    children_[pos - 1]->next_ = child;
  }
  if (*(children_.end() - 1) != child) {
    children_[pos + 1]->prev_ = child;
  }
}
std::shared_ptr<radix::Expression>& radix::Expression::at(std::size_t pos) {
  return children_.at(pos);
}

void radix::Expression::append(std::shared_ptr<Expression> child) {
  children_.push_back(child);
  if (*(children_.begin()) != child) {
    (*(children_.end() - 1))->next_ = child;
  }
}

void radix::Expression::prepend(std::shared_ptr<Expression> child) {
  children_.insert(children_.begin(), child);
  if (*(children_.end() - 1) != child) {
    (*(children_.begin() + 1))->prev_ = child;
  }
}

void radix::Expression::clear() { children_.clear(); }

std::vector<std::shared_ptr<radix::Expression>>::iterator
radix::Expression::begin() {
  return children_.begin();
}
std::vector<std::shared_ptr<radix::Expression>>::iterator
radix::Expression::end() {
  return children_.end();
}
std::shared_ptr<radix::Expression>& radix::Expression::front() {
  return children_.front();
}
std::shared_ptr<radix::Expression>& radix::Expression::back() {
  return children_.back();
}

bool radix::Expression::IsLeaf() const { return children_.size() == 0; }
bool radix::Expression::HasOnlyLeafs() const {
  bool ret = true;
  for (auto& it : children_) {
    ret = ret && it->IsLeaf();
  }
  return ret;
}

std::shared_ptr<radix::Expression> radix::GenerateExpression(
    std::string_view str) {
  return std::make_shared<Expression>(Expression());
}

std::shared_ptr<radix::Expression> radix::CopyExpression(
    std::shared_ptr<Expression> exp) {
  std::shared_ptr<Expression> ret = std::make_shared<Expression>(Expression());
  if (exp->type_ == VALUE) {
    ret = CopyValue(exp);
  } else if (exp->type_ == FUNCTION) {
    ret = CopyFunction(exp);
  }
  ret->type_ = exp->type_;
  if (exp->next_) {
    ret->next_ = std::make_shared<Expression>(*(exp->next_));
  }
  if (exp->prev_) {
    ret->prev_ = std::make_shared<Expression>(*(exp->prev_));
  }
  for (auto& it : exp->children_) {
    ret->append(CopyExpression(it));
  }
  return ret;
}

std::shared_ptr<radix::Expression> radix::CopyExpression(
    const Expression* exp) {
  std::shared_ptr<Expression> ret = std::make_shared<Expression>(Expression());
  if (exp->type_ == VALUE) {
    ret = CopyValue(exp);
  } else if (exp->type_ == FUNCTION) {
    ret = CopyFunction(exp);
  }
  ret->type_ = exp->type_;
  if (exp->next_) {
    ret->next_ = std::make_shared<Expression>(*(exp->next_));
  }
  if (exp->prev_) {
    ret->prev_ = std::make_shared<Expression>(*(exp->prev_));
  }
  for (auto& it : exp->children_) {
    ret->append(CopyExpression(it));
  }
  return ret;
}

std::shared_ptr<radix::Expression> radix::Eval(
    std::shared_ptr<Expression> exp,
    std::vector<std::shared_ptr<Expression>> vals) {
  std::shared_ptr<Expression> cpy = CopyExpression(exp);
  for(auto &it : vals){
    cpy->SetVariable(it);
  }
  return Eval_(cpy);
}

std::shared_ptr<radix::Expression> radix::Eval_(
    std::shared_ptr<Expression> exp) {
  if (!exp->HasOnlyLeafs()) {
    for (auto& it : exp->children_) {
      it = Eval_(it);
    }
  }
  if (exp->type_ == FUNCTION) {
    return std::dynamic_pointer_cast<FunctionBase>(exp)->eval();
  } else {
    return exp;
  }
}
