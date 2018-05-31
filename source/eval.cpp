#include "eval.hpp"

#include "function/operator.hpp"
#include "value/value.hpp"
#include "value/variable.hpp"

radix::Expression radix::Eval(Expression tree, std::map<std::string, Expression> args){
  Expression ret = SetVariables(tree, args);
  Eval(ret);
  return ret;
}

void radix::Eval(Expression &tree){
  if(tree.child_size() == 0){
    return;
  }
  for(auto it = tree.child_begin(); it != tree.child_end(); ++it){
    Eval(*it.node_);
  }
  if(tree.node->type_ == OPERATOR){
    tree = EvalOp(tree);
    tree.clear();
  }
}

radix::Expression radix::EvalOp(Expression tree){
  std::shared_ptr<radix::Operator> op = std::dynamic_pointer_cast<radix::Operator>(tree.node);
  return Expression(op->Eval(*(++tree.begin()), *(--tree.end())));
}

radix::Expression radix::SetVariables(Expression tree, std::map<std::string, Expression> args){
  for(auto it = tree.begin(); it != tree.end(); ++it){
    if(it.node_->node->type_ == VARIABLE){
      std::map<std::string, Expression>::iterator arg;
      if((arg = args.find(std::dynamic_pointer_cast<radix::Variable>(*it)->GetRef())) != args.end()){
        tree.replace(it, arg->second);
      }
    }
  }
  return tree;
}
