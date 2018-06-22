#include "eval.hpp"

#include "function/function.hpp"
#include "function/operator.hpp"
#include "value/value.hpp"
#include "value/variable.hpp"

radix::Expression radix::Eval(Expression tree,
                              std::map<std::string, Expression> args) {
  Expression ret = SetVariables(tree, args);
  Eval(ret);
  return ret;
}

void radix::Eval(Expression& tree) {
  if (tree.child_size() == 0) {
    return;
  }
  for (auto it = tree.child_begin(); it != tree.child_end(); ++it) {
    Eval(*it.node_);
  }
  for (auto it = tree.fixed_begin(); it != tree.fixed_end(); ++it) {
    if ((*it)->type_ == VARIABLE) {
      return;
    }
  }
  if (tree.node->type_ == OPERATOR) {
    tree = EvalOp(tree);
    tree.clear();
  } else if (tree.node->type_ == FUNCTION) {
    tree = EvalFunc(tree);
    tree.clear();
  }
}

radix::Expression radix::EvalOp(Expression tree) {
  std::shared_ptr<radix::Operator> op =
      std::dynamic_pointer_cast<radix::Operator>(tree.node);
  return Expression(op->Eval(*(++tree.begin()), *(--tree.end())));
}
radix::Expression radix::EvalFunc(Expression tree) {
  std::shared_ptr<radix::Function> func =
      std::dynamic_pointer_cast<radix::Function>(tree.node);
  if (func->nargs_ == 1) {
    return Expression(func->Eval(*(++tree.begin())));
  }else if(func->nargs_ == 2){
    return Expression(func->Eval(*(++tree.begin()), *(tree.begin()+2)));
  }else{
    return tree;
  }
}

radix::Expression radix::SetVariables(Expression tree,
                                      std::map<std::string, Expression> args) {
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    if (it.node_->node->type_ == VARIABLE) {
      std::map<std::string, Expression>::iterator arg;
      if ((arg = args.find(
               std::dynamic_pointer_cast<radix::Variable>(*it)->GetRef())) !=
          args.end()) {
        tree.replace(it, arg->second);
      }
    }
  }
  return tree;
}
