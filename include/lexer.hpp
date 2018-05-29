#ifndef RADIX_LEXER_HPP_
#define RADIX_LEXER_HPP_

#include <array>
#include <map>
#include <queue>
#include <string>

#include <tree.hpp>

#include "expression_base.hpp"

namespace radix {
class Lexer {
 private:
  enum TokenType {
    EOS = 0,
    NUMERIC = 1,
    VARIABLE = 2,
    FUNCTION = 3,
    OPERATOR = 4,
    OPEN_PAREN = 5,
    CLOSE_PAREN = 6
  };

 public:
  Lexer();
  ~Lexer();

  estl::tree::Tree<std::shared_ptr<ExpressionBase>> Parse(std::string exp);

  std::queue<std::pair<std::string, TokenType>> GetTokenQueue(std::string exp);
  void SetExpression(std::string str);
  std::pair<std::string, TokenType> GetNextToken();

  void LoadOperators();
  void LoadFunctions();

  void AddOperator(std::string op, int prec, int nargs);
  void AddFunction(std::string func, int nargs);

 private:
  bool IsSpace(char ch);
  bool IsDigit(char ch);
  bool IsDecimal(char ch);
  bool IsParen(char ch);
  bool StartsWith(std::string src, std::string prefix);
  bool HasMatch(std::string token);
  bool IsMatch(std::string token);

  bool TokenIsNumeric(std::string token);
  bool TokenIsVariable(std::string token);
  bool TokenIsFunction(std::string token);
  bool TokenIsOperator(std::string token);
  bool TokenIsOpenParen(std::string token);
  bool TokenIsCloseParen(std::string token);

  std::string GetMatching(std::string token);

  std::size_t pos_;
  std::string expression_;

  std::map<std::string, std::array<int, 3>> operators_;
  std::map<std::string, std::array<int, 2>> functions_;
};
}  // namespace radix

#endif  // RADIX_LEXER_HPP_
