#ifndef RADIX_PARSER_PARSER_HPP_
#define RADIX_PARSER_PARSER_HPP_

#include <memory>

#include "lexer.hpp"

namespace radix {
  template <typename _Lexer>
  class Parser{
    public:
      Parser();

      void Parse(std::string);
    protected:
    private:
      _Lexer lexer_;
  };
} // namespace radix

#endif  // RADIX_PARSER_PARSER_HPP_
