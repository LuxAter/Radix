#ifndef RADIX_PARSER_HPP_
#define RADIX_PARSER_HPP_

#include "lexer.hpp"

namespace radix {
  void parse_init();
  void parse_error(TokenType expected, TokenType actual);
  void parse_eat(const TokenType& type);
  double expression();
  double additive_expression();
  double multiplicative_expression();
  double exponential_expression();
  double postfix_expression();
  double primary_expression();
  double eval_func(std::string func, double vars[5]);
} // namespace radix

#endif  // RADIX_PARSER_HPP_
