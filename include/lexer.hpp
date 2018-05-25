#ifndef RADIX_LEXER_HPP_
#define RADIX_LEXER_HPP_

#include <string>
#include <map>
#include <array>
#include <queue>

namespace radix {
  class Lexer{
    public:
      Lexer();
      ~Lexer();

      void Parse(std::string exp);

      std::queue<std::string> GetTokenQueue(std::string exp);
      void SetExpression(std::string str);
      std::string GetNextToken();

      void LoadOperators();
      void LoadFunctions();
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
} // namespace radix

#endif  // RADIX_LEXER_HPP_
