#include "eval.hpp"

#include "value/value.hpp"
#include "value/variable.hpp"

radix::Expression radix::Eval(Expression tree, std::map<std::string, std::shared_ptr<radix::ExpressionBase>> args){
  for(auto it = tree.leaf_begin(); it != tree.leaf_end(); ++it){
    if(it.node_->node->type_ == VARIABLE){
      std::map<std::string, std::shared_ptr<ExpressionBase>>::iterator arg;
      if((arg = args.find(std::dynamic_pointer_cast<radix::Variable>(*it)->GetRef())) != args.end()){
        tree.insert(it, arg->second);
      }
      // tree.insert(it, args)
    }
  }
  return tree;
}
