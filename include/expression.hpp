#ifndef RADIX_EXPRESSION_HPP_
#define RADIX_EXPRESSION_HPP_

#include <memory>
#include <string>

#include <tree.hpp>

#include "expression_base.hpp"
#include "lexer.hpp"

namespace radix {
  typedef estl::tree::Tree<std::shared_ptr<ExpressionBase>> Expression;

  std::string PrintAST(const Expression exp);
  std::string PrintAST(const Expression *exp);
} // namespace radix

#endif  // RADIX_EXPRESSION_HPP_
