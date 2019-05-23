#ifndef RADIX_HPP_
#define RADIX_HPP_

#include "lexer.hpp"
#include "parser.hpp"

#include <vector>

namespace radix {
double eval(std::string str);
void plot_func();
std::string get_ch(unsigned x, unsigned y, std::vector<double> data,
                   double max_v, double step);
}  // namespace radix

#endif  // RADIX_HPP_
