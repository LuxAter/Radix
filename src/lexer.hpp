#ifndef RADIX_LEXER_HPP_
#define RADIX_LEXER_HPP_
#include <string>

namespace radix {
  enum TokenType{
    REAL, ADDITIVE, MULTIPLICATIVE, POW, FAC, LPAREN, RPAREN, ID, EOS
  };
  struct Token{
    TokenType type;
    std::string str_val;
    double val;
  };

  void lex_init(const char* text);
  void lex_error();
  void lex_advance();
  char lex_peek();
  void lex_skip_whitespace();
  void lex_skip_comment();
  double lex_number();
  std::string lex_id();
  Token get_next_token();
  size_t lex_line();
  size_t lex_col();
} // namespace radix
#endif  // RADIX_LEXER_HPP_
