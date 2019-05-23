#ifndef RADIX_LEXER_HPP_
#define RADIX_LEXER_HPP_
#include <string>

namespace radix {
  enum TokenType{
    REAL, ADDITIVE, MULTIPLICATIVE, POW, FAC, LPAREN, RPAREN, ID, COMMA, EQUAL, EOS
  };
  struct Token{
    TokenType type;
    std::string str_val;
    double val;
  };
  struct LexState{
    char current_char;
    size_t line, col, pos;
    Token current_token;
  };

  void lex_init(const char* text);
  void lex_error();
  void lex_advance();
  char lex_peek();
  char lex_current();
  void lex_skip_whitespace();
  void lex_skip_comment();
  double lex_number();
  std::string lex_id();
  Token get_next_token();
  size_t lex_line();
  size_t lex_col();
  LexState lex_get_state();
  void lex_restore_state(LexState state);
} // namespace radix
#endif  // RADIX_LEXER_HPP_
