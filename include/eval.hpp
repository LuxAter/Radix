#ifndef RADIX_EVAL_HPP_
#define RADIX_EVAL_HPP_

#include <memory>
#include <string>

#include <tree.hpp>

#include "expression.hpp"
#include "expression_base.hpp"
#include "lexer.hpp"

namespace radix {
  Expression Eval(Expression tree, std::map<std::string, std::shared_ptr<ExpressionBase>> args);
} // namespace radix

#endif  // RADIX_EVAL_HPP_
