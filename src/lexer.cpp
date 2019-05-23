#include "lexer.hpp"

#include <cstring>
#include <string>

#include <iostream>

static const char* buff = NULL;
static char current_char = 0;
static size_t len = 0, line = 0, col = 0, pos = 0;
radix::Token current_token = radix::Token{radix::EOS, "", 0.0};

void radix::lex_init(const char* text) {
  buff = text;
  len = std::strlen(buff);
  line = 0;
  col = 0;
  pos = 0;
  current_char = buff[0];
}
void radix::lex_error() {
  fprintf(stderr, "Unexpected token at line: %lu, column: %lu\n", line, col);
  exit(1);
}
void radix::lex_advance() {
  pos++;
  col++;
  if (pos >= len) {
    current_char = 0;
  } else {
    current_char = buff[pos];
    if (current_char == '\n') {
      line++;
      col = 0;
    }
  }
}
char radix::lex_peek() {
  if (pos >= len - 1) {
    return 0;
  } else {
    return buff[pos + 1];
  }
}
void radix::lex_skip_whitespace() {
  while (current_char != 0 &&
         (current_char == ' ' || current_char == '\t' || current_char == '\n'))
    lex_advance();
}
void radix::lex_skip_comment() {
  while (current_char != 0 && current_char != '\n') lex_advance();
}
double radix::lex_number() {
  std::string result = "";
  while (current_char != 0 && (current_char >= 48 && current_char <= 57)) {
    result += current_char;
    lex_advance();
  }
  if (current_char == '.') {
    result += '.';
    lex_advance();
    while (current_char != 0 && (current_char >= 48 && current_char <= 57)) {
      result += current_char;
      lex_advance();
    }
  }
  if (current_char == 'e') {
    result += 'e';
    lex_advance();
    while (current_char != 0 && (current_char >= 48 && current_char <= 57)) {
      result += current_char;
      lex_advance();
    }
    if (current_char == '.') {
      result += '.';
      lex_advance();
      while (current_char != 0 && (current_char >= 48 && current_char <= 57)) {
        result += current_char;
        lex_advance();
      }
    }
  }
  return stod(result);
}
std::string radix::lex_id() {
  std::string result = "";
  while (current_char != 0 && ((current_char >= 48 && current_char <= 57) ||
                               (current_char >= 65 && current_char <= 90) ||
                               (current_char >= 97 && current_char <= 122) ||
                               (current_char == 95))) {
    result += current_char;
    lex_advance();
  }
  return result;
}
radix::Token radix::get_next_token() {
  while (current_char != 0) {
    if (current_char == ' ' || current_char == '\t' || current_char == '\n') {
      lex_skip_whitespace();
      continue;
    } else if ((current_char >= 48 && current_char <= 57) ||
               current_char == '.') {
      return Token{REAL, "", lex_number()};
    } else if (current_char == '+' || current_char == '-') {
      Token tok{ADDITIVE, std::string(1, current_char), 0.0};
      lex_advance();
      return tok;
    } else if (current_char == '*' || current_char == '/' ||
               current_char == '%') {
      Token tok{MULTIPLICATIVE, std::string(1, current_char), 0.0};
      lex_advance();
      return tok;
    } else if (current_char == '^') {
      Token tok{POW, std::string(1, current_char), 0.0};
      lex_advance();
      return tok;
    } else if (current_char == '!') {
      Token tok{FAC, std::string(1, current_char), 0.0};
      lex_advance();
      return tok;
    } else if (current_char == '(') {
      Token tok{LPAREN, "(", 0.0};
      lex_advance();
      return tok;
    } else if (current_char == ')') {
      Token tok{RPAREN, ")", 0.0};
      lex_advance();
      return tok;
    } else if ((current_char >= 65 && current_char <= 90) ||
               (current_char >= 97 && current_char <= 122) ||
               (current_char == 95)) {
      return Token{ID, lex_id(), 0.0};
    }
    lex_error();
  }
  return Token{EOS, "", 0.0};
}

size_t radix::lex_line() { return line; }
size_t radix::lex_col() { return col; }
