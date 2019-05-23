#include "parser.hpp"

#include <cmath>

#include "lexer.hpp"

#include <iostream>
#include <map>

static radix::Token current_token;
static std::map<std::string, double> consts = {
    {"pi", M_PI}, {"inf", INFINITY}, {"nan", NAN}};
static std::map<std::string, short> func_nargs = {{"abs", 1},
                                                  {"mod", 2},
                                                  {"remainder", 2},
                                                  {"fma", 3},
                                                  {"max", 2},
                                                  {"min", 2},
                                                  {"dim", 2},
                                                  // {"lerp", 3},
                                                  {"exp", 1},
                                                  {"exp2", 1},
                                                  {"expm1", 1},
                                                  {"log", 1},
                                                  {"log10", 1},
                                                  {"log2", 1},
                                                  {"log1p", 1},
                                                  {"pow", 2},
                                                  {"sqrt", 1},
                                                  {"cbrt", 1},
                                                  {"hypot", 2},
                                                  {"sin", 1},
                                                  {"cos", 1},
                                                  {"tan", 1},
                                                  {"asin", 1},
                                                  {"acos", 1},
                                                  {"atan", 1},
                                                  {"atan2", 2},
                                                  {"sinh", 1},
                                                  {"cosh", 1},
                                                  {"tanh", 1},
                                                  {"asinh", 1},
                                                  {"acosh", 1},
                                                  {"atanh", 1},
                                                  {"erf", 1},
                                                  {"erfc", 1},
                                                  {"tgamma", 1},
                                                  {"lgamma", 1},
                                                  {"ceil", 1},
                                                  {"floor", 1},
                                                  {"trunc", 1},
                                                  {"round", 1},
                                                  {"nearbyint", 1},
                                                  {"rint", 1},
                                                  {"assoc_laguerre", 3},
                                                  {"assoc_legendre", 3},
                                                  {"beta", 2},
                                                  {"comp_ellint_1", 1},
                                                  {"comp_ellint_2", 1},
                                                  {"comp_ellint_3", 2},
                                                  {"cyl_bessel_i", 2},
                                                  {"cyl_bessel_j", 2},
                                                  {"cyl_bessel_k", 2},
                                                  {"cyl_neumann", 2},
                                                  {"ellint_1", 2},
                                                  {"ellint_2", 2},
                                                  {"ellint_3", 3},
                                                  {"expint", 1},
                                                  {"hermite", 2},
                                                  {"legendre", 2},
                                                  {"laguerre", 2},
                                                  {"riemann_zeta", 1},
                                                  {"sph_bessel", 2},
                                                  {"sph_legendre", 3},
                                                  {"sph_neumann", 2}};

void radix::parse_init() { current_token = get_next_token(); }

void radix::parse_error(TokenType expected, TokenType actual) {
  fprintf(stderr, "Syntax Error Line: %lu Col: %lu\n", lex_line(), lex_col());
  fprintf(stderr, "             Expected %u got %u\n", expected, actual);
  exit(2);
}

void radix::parse_eat(const TokenType& type) {
  if (current_token.type == type) {
    current_token = get_next_token();
  } else {
    parse_error(type, current_token.type);
  }
}

double radix::expression() { return additive_expression(); }
double radix::additive_expression() {
  double result = multiplicative_expression();
  if (current_token.type == ADDITIVE) {
    if (current_token.str_val == "+") {
      parse_eat(ADDITIVE);
      result += additive_expression();
    } else if (current_token.str_val == "-") {
      parse_eat(ADDITIVE);
      result -= additive_expression();
    }
  }
  return result;
}
double radix::multiplicative_expression() {
  double result = exponential_expression();
  if (current_token.type == MULTIPLICATIVE) {
    if (current_token.str_val == "*") {
      parse_eat(MULTIPLICATIVE);
      result *= multiplicative_expression();
    } else if (current_token.str_val == "/") {
      parse_eat(MULTIPLICATIVE);
      result /= multiplicative_expression();
    } else if (current_token.str_val == "%") {
      parse_eat(MULTIPLICATIVE);
      result = std::fmod(result, multiplicative_expression());
    }
  }
  return result;
}
double radix::exponential_expression() {
  double result = postfix_expression();
  if (current_token.type == POW) {
    parse_eat(POW);
    result = std::pow(result, exponential_expression());
  }
  return result;
}
double radix::postfix_expression() {
  double result = primary_expression();
  if (current_token.type == FAC) {
    parse_eat(FAC);
    for (unsigned long i = std::floor(result) - 1; i > 0; i--) {
      result *= static_cast<double>(i);
    }
  } else if (current_token.type == ID) {
    std::string func = current_token.str_val;
    parse_eat(FAC);
    parse_eat(LPAREN);
    parse_eat(RPAREN);
  }
  return result;
}
double radix::primary_expression() {
  Token token = current_token;
  if (token.type == REAL) {
    parse_eat(REAL);
    return token.val;
  } else if (token.type == LPAREN) {
    parse_eat(LPAREN);
    double result = expression();
    parse_eat(RPAREN);
    return result;
  } else if (token.type == ID) {
    parse_eat(ID);
    if (consts.find(token.str_val) != consts.end()) {
      return consts[token.str_val];
    } else if (func_nargs.find(token.str_val) != func_nargs.end()) {
      parse_eat(LPAREN);
      double vars[5];
      for (short i = 0; i < func_nargs[token.str_val]; ++i) {
        vars[i] = expression();
      }
      parse_eat(RPAREN);
      return eval_func(token.str_val, vars);
    } else {
      parse_error(REAL, token.type);
    }
  } else {
    parse_error(REAL, token.type);
  }
  return 0.0;
}

double radix::eval_func(std::string func, double vars[5]) {
  if (func == "abs")
    return std::fabs(vars[0]);
  else if (func == "mod")
    return std::fmod(vars[0], vars[1]);
  else if (func == "remainder")
    return std::remainder(vars[0], vars[1]);
  else if (func == "fma")
    return std::fmaf(vars[0], vars[1], vars[2]);
  else if (func == "max")
    return std::max(vars[0], vars[1]);
  else if (func == "min")
    return std::min(vars[0], vars[1]);
  else if (func == "dim")
    return std::fdim(vars[0], vars[1]);
  // else if(func == "lerp") return std::lerp(vars[0], vars[1], vars[2]); XXX
  // C++20
  else if (func == "exp")
    return std::exp(vars[0]);
  else if (func == "exp2")
    return std::exp2(vars[0]);
  else if (func == "expm1")
    return std::expm1(vars[0]);
  else if (func == "log")
    return std::log(vars[0]);
  else if (func == "log10")
    return std::log10(vars[0]);
  else if (func == "log2")
    return std::log2(vars[0]);
  else if (func == "log1p")
    return std::log1p(vars[0]);
  else if (func == "pow")
    return std::pow(vars[0], vars[1]);
  else if (func == "sqrt")
    return std::sqrt(vars[0]);
  else if (func == "cbrt")
    return std::cbrt(vars[0]);
  else if (func == "hypot")
    return std::hypot(vars[0], vars[2]);
  else if (func == "sin")
    return std::sin(vars[0]);
  else if (func == "cos")
    return std::cos(vars[0]);
  else if (func == "tan")
    return std::tan(vars[0]);
  else if (func == "asin")
    return std::asin(vars[0]);
  else if (func == "acos")
    return std::acos(vars[0]);
  else if (func == "atan")
    return std::atan(vars[0]);
  else if (func == "atan2")
    return std::atan2(vars[0], vars[1]);
  else if (func == "sinh")
    return std::sinh(vars[0]);
  else if (func == "cosh")
    return std::cosh(vars[0]);
  else if (func == "tanh")
    return std::tanh(vars[0]);
  else if (func == "asinh")
    return std::asinh(vars[0]);
  else if (func == "acosh")
    return std::acosh(vars[0]);
  else if (func == "atanh")
    return std::atanh(vars[0]);
  else if (func == "erf")
    return std::erf(vars[0]);
  else if (func == "erfc")
    return std::erfc(vars[0]);
  else if (func == "tgamma")
    return std::tgamma(vars[0]);
  else if (func == "lgamma")
    return std::lgamma(vars[0]);
  else if (func == "ceil")
    return std::ceil(vars[0]);
  else if (func == "floor")
    return std::floor(vars[0]);
  else if (func == "trunc")
    return std::trunc(vars[0]);
  else if (func == "round")
    return std::round(vars[0]);
  else if (func == "nearbyint")
    return std::nearbyint(vars[0]);
  else if (func == "rint")
    return std::rint(vars[0]);
  else if (func == "assoc_laguerre")
    return std::assoc_laguerre(vars[0], vars[1], vars[2]);
  else if (func == "assoc_legendre")
    return std::assoc_legendre(vars[0], vars[1], vars[2]);
  else if (func == "beta")
    return std::beta(vars[0], vars[1]);
  else if (func == "comp_ellint_1")
    return std::comp_ellint_1(vars[0]);
  else if (func == "comp_ellint_2")
    return std::comp_ellint_2(vars[0]);
  else if (func == "comp_ellint_3")
    return std::comp_ellint_3(vars[0], vars[1]);
  else if (func == "cyl_bessel_i")
    return std::cyl_bessel_i(vars[0], vars[1]);
  else if (func == "cyl_bessel_j")
    return std::cyl_bessel_j(vars[0], vars[1]);
  else if (func == "cyl_bessel_k")
    return std::cyl_bessel_k(vars[0], vars[1]);
  else if (func == "cyl_neumann")
    return std::cyl_neumann(vars[0], vars[1]);
  else if (func == "ellint_1")
    return std::ellint_1(vars[0], vars[1]);
  else if (func == "ellint_2")
    return std::ellint_2(vars[0], vars[1]);
  else if (func == "ellint_3")
    return std::ellint_3(vars[0], vars[1], vars[2]);
  else if (func == "expint")
    return std::expint(vars[0]);
  else if (func == "hermite")
    return std::hermite(vars[0], vars[1]);
  else if (func == "legendre")
    return std::legendre(vars[0], vars[1]);
  else if (func == "laguerre")
    return std::laguerre(vars[0], vars[1]);
  else if (func == "riemann_zeta")
    return std::riemann_zeta(vars[0]);
  else if (func == "sph_bessel")
    return std::sph_bessel(vars[0], vars[1]);
  else if (func == "sph_legendre")
    return std::sph_legendre(vars[0], vars[1], vars[2]);
  else if (func == "sph_neumann")
    return std::sph_neumann(vars[0], vars[1]);
  else
    return 0.0;
}
