#ifndef RADIX_PARSER_HPP_
#define RADIX_PARSER_HPP_

#include "lexer.hpp"

namespace radix {
void parse_init();
void parse_error(TokenType expected, TokenType actual);
void parse_eat(const TokenType& type);
Token parse_current();
double& parse_global(const std::string& key);
void parse_restore(LexState state);

double expression();
double assignment_expression();
double additive_expression();
double multiplicative_expression();
double exponential_expression();
double unary_expression();
double postfix_expression();
double primary_expression();
double eval_func(std::string func, double vars[5]);
double eval_special_func(std::string func);
}  // namespace radix

#endif  // RADIX_PARSER_HPP_
