#include "expression.hpp"

#include <memory>
#include <string>
#include <vector>

#include <tree.hpp>

#include "expression_base.hpp"
#include "lexer.hpp"

std::string radix::PrintAST(const Expression exp){
  return PrintAST(&exp);
}

std::string radix::PrintAST(const Expression *exp){
  std::string ret = exp->node->Latex(false);
  if(exp->child_size() != 0){
    ret += '[';
    for(auto it = exp->cchild_begin(); it != exp->cchild_end(); ++it){
      ret += PrintAST(it.node_);
      if(it != (--exp->cchild_end())){
        ret += ',';
      }
    }
    ret += ']';
  }
  return ret;
}
