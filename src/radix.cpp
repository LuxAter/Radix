#include "radix.hpp"

#include <cmath>
#include <map>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"

#include <iostream>

// static std::map<uint8_t, std::string> brail = {{0x00, "\u2800"},
//                                                {0x80, "\u2801"},
//                                                {0x40, "\u2802"},
//                                                {0x}}

double radix::eval(std::string str) {
  lex_init(str.c_str());
  parse_init();
  if (parse_current().type == ID && parse_current().str_val == "plot") {
    parse_eat(ID);
    plot_func();
    return NAN;
  }
  return expression();
}

void radix::plot_func() {
  double start = 0;
  double stop = 0;
  double step = 1;
  parse_eat(LPAREN);
  Token var = parse_current();
  parse_global(var.str_val) = 0.0;
  parse_eat(ID);
  LexState state = lex_get_state();
  parse_eat(COMMA);
  expression();
  if (parse_current().type == COMMA) {
    parse_eat(COMMA);
    start = expression();
  }
  if (parse_current().type == COMMA) {
    parse_eat(COMMA);
    stop = expression();
  }
  step = (stop - start) / 80;
  parse_eat(RPAREN);
  std::vector<double> data;
  double min_v = INFINITY;
  double max_v = -INFINITY;
  for (parse_global(var.str_val) = start; parse_global(var.str_val) <= stop;
       parse_global(var.str_val) += step) {
    parse_restore(state);
    data.push_back(expression());
    // std::cout << data.back() << "!!\n";
    min_v = std::min(data.back(), min_v);
    max_v = std::max(data.back(), max_v);
  }
  // std::cout << min_v << ":" << max_v << "\n";
  double ystep = (max_v - min_v) / 80;
  // std::cout << ystep << "!!\n";
  for (unsigned y = 0; y < 80; y += 4) {
    for (unsigned x = 0; x < 80; x += 2) {
      std::cout << get_ch(x, y, data, max_v, ystep);
    }
    printf("\n");
  }
}

std::string radix::get_ch(unsigned x, unsigned y, std::vector<double> data,
                          double max_v, double step) {
  uint16_t bits = 0;
  // std::cout << data[x] << ":" << max_v - (step * y) << ":"
  //           << max_v - (step * (y + 4)) << "\n";
  if (max_v - (step * y) >= data[x] && data[x] >= max_v - (step * (y + 1))) {
    bits |= 0x01;
  }
  if (max_v - (step * (y + 1)) >= data[x] &&
      data[x] > max_v - (step * (y + 2))) {
    bits |= 0x02;
  }
  if (max_v - (step * (y + 2)) >= data[x] &&
      data[x] > max_v - (step * (y + 3))) {
    bits |= 0x04;
  }
  if (max_v - (step * (y + 3)) >= data[x] &&
      data[x] > max_v - (step * (y + 4))) {
    bits |= 0x40;
  }
  if (max_v - (step * y) >= data[x + 1] &&
      data[x + 1] > max_v - (step * (y + 1))) {
    bits |= 0x08;
  }
  if (max_v - (step * (y + 1)) >= data[x + 1] &&
      data[x + 1] > max_v - (step * (y + 2))) {
    bits |= 0x10;
  }
  if (max_v - (step * (y + 2)) >= data[x + 1] &&
      data[x + 1] > max_v - (step * (y + 3))) {
    bits |= 0x20;
  }
  if (max_v - (step * (y + 3)) >= data[x + 1] &&
      data[x + 1] > max_v - (step * (y + 4))) {
    bits |= 0x80;
  }
  bits += 10240;
  std::string out;

  if (bits <= 0x7f) {
    out.append(1, static_cast<char>(bits));
  } else if (bits <= 0x7ff) {
    out.append(1, static_cast<char>(0xc0 | ((bits >> 6) & 0x1f)));
    out.append(1, static_cast<char>(0x80 | (bits & 0x3f)));
  } else if (bits <= 0xffff) {
    out.append(1, static_cast<char>(0xe0 | ((bits >> 12) & 0x0f)));
    out.append(1, static_cast<char>(0x80 | ((bits >> 6) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | (bits & 0x3f)));
  } else {
    out.append(1, static_cast<char>(0xf0 | ((bits >> 18) & 0x07)));
    out.append(1, static_cast<char>(0x80 | ((bits >> 12) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | ((bits >> 6) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | (bits & 0x3f)));
  }
  return out;
}

// std::string tui::Buffer::GetChar(unsigned int ch) {
//   std::string out;
//
//   if (ch <= 0x7f) {
//     out.append(1, static_cast<char>(ch));
//   } else if (ch <= 0x7ff) {
//     out.append(1, static_cast<char>(0xc0 | ((ch >> 6) & 0x1f)));
//     out.append(1, static_cast<char>(0x80 | (ch & 0x3f)));
//   } else if (ch <= 0xffff) {
//     out.append(1, static_cast<char>(0xe0 | ((ch >> 12) & 0x0f)));
//     out.append(1, static_cast<char>(0x80 | ((ch >> 6) & 0x3f)));
//     out.append(1, static_cast<char>(0x80 | (ch & 0x3f)));
//   } else {
//     out.append(1, static_cast<char>(0xf0 | ((ch >> 18) & 0x07)));
//     out.append(1, static_cast<char>(0x80 | ((ch >> 12) & 0x3f)));
//     out.append(1, static_cast<char>(0x80 | ((ch >> 6) & 0x3f)));
//     out.append(1, static_cast<char>(0x80 | (ch & 0x3f)));
//   }
//   return out;
// }
