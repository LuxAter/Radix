#include "radix.hpp"

#include <string>

#include "lexer.hpp"
#include "parser.hpp"

double radix::eval(std::string str){
  lex_init(str.c_str());
  parse_init();
  return expression();
}
