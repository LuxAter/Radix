#include "lexer.hpp"

#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "estl/logger.hpp"

using namespace estl::logger;

radix::Lexer::Lexer() {}
radix::Lexer::~Lexer() {}

void radix::Lexer::Parse(std::string exp){
  std::queue<std::string> token_queue = GetTokenQueue(exp);
  while(token_queue.size() != 0){
    std::cout << token_queue.front() << ' ';
    token_queue.pop();
  }
  std::cout << '\n';
}

std::queue<std::string> radix::Lexer::GetTokenQueue(std::string exp) {
  expression_ = exp;
  pos_ = 0;
  std::queue<std::string> token_queue;
  std::stack<std::string> operator_stack;
  std::string token;
  while (token != "EOS") {
    token = GetNextToken();
    if(token == "EOS"){
      break;
    }
    std::cout << ">>" << token << "\n";
    if (TokenIsNumeric(token) || TokenIsVariable(token)) {
      token_queue.push(token);
    } else if (TokenIsFunction(token)) {
      operator_stack.push(token);
    } else if (TokenIsOperator(token)) {
      while (operator_stack.size() != 0 && (TokenIsFunction(operator_stack.top()) ||
              operators_[operator_stack.top()][0] > operators_[token][0] ||
              (operators_[operator_stack.top()][0] == operators_[token][0] &&
               !operators_[operator_stack.top()][2])) &&
             !TokenIsOpenParen(operator_stack.top())) {
        token_queue.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.push(token);
    } else if (TokenIsOpenParen(token)) {
      operator_stack.push(token);
    } else if (TokenIsCloseParen(token)) {
      std::string matching = GetMatching(token);
      while (operator_stack.top() != matching) {
        if (TokenIsOpenParen(operator_stack.top())) {
          estl::logger::Error("Unclosed parentheses block");
        }
        token_queue.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
    }else if(token == ","){
      while(!TokenIsOpenParen(operator_stack.top())){
        token_queue.push(operator_stack.top());
        operator_stack.pop();
      }
    }
  }
  while (operator_stack.size() != 0) {
    token_queue.push(operator_stack.top());
    operator_stack.pop();
  }
  return token_queue;
}

void radix::Lexer::SetExpression(std::string str) {
  expression_ = str;
  pos_ = 0;
}

std::string radix::Lexer::GetNextToken() {
  if (pos_ >= expression_.size()) {
    return "EOS";
  }
  std::string res;
  std::size_t local = 0;
  bool is_num = false;
  bool has_decimal = false;
  char current = expression_[pos_];
  while (IsSpace(current)) {
    pos_++;
    current = expression_[pos_];
  }
  while (current != 0) {
    current = expression_[pos_ + local];
    if (local == 0) {
      if (IsDigit(current)) {
        is_num = true;
      } else if (IsDecimal(current)) {
        is_num = true;
        has_decimal = true;
      } else if (IsParen(current)) {
        local++;
        res += current;
        break;
      }else if(current == ','){
        local++;
        res += current;
        break;
      }
    } else {
      if (!is_num && IsDigit(current)) {
        break;
      } else if (IsParen(current)) {
        break;
      } else if (is_num && IsDecimal(current)) {
        if (has_decimal) {
          estl::logger::Error("Numeric token already has decimal");
          break;
        } else {
          has_decimal = true;
        }
      } else if (IsMatch(res) && !HasMatch(res + current)) {
        break;
      } else if (IsMatch(std::string(1, current))) {
        break;
      } else if (is_num && !IsDigit(current)) {
        expression_.insert(expression_.begin() + pos_ + local, '*');
        break;
      } else if(current == ','){
        break;
      }
    }
    res += current;
    local++;
  }
  pos_ += local;
  return res;
}

void radix::Lexer::LoadOperators() {
  operators_["+"] = {2, 2, 1};
  operators_["-"] = {2, 2, 1};
  operators_["*"] = {3, 2, 1};
  operators_["/"] = {3, 2, 1};
  operators_["^"] = {4, 2, 0};
  operators_["!"] = {4, 1, 0};
  operators_["="] = {-2, 2, 1};
  operators_["!="] = {-2, 2, 1};
  operators_[">="] = {-2, 2, 1};
  operators_["<="] = {-2, 2, 1};
  operators_[">"] = {-2, 2, 1};
  operators_["<"] = {-2, 2, 1};
}

void radix::Lexer::LoadFunctions() {
  functions_["sin"] = {-1, 1};
  functions_["cos"] = {-1, 1};
  functions_["tan"] = {-1, 1};
  functions_["pow"] = {-1, 2};
  functions_["max"] = {-1, 2};
  functions_["min"] = {-1, 2};
}

bool radix::Lexer::IsSpace(char ch) { return (ch == 32); }
bool radix::Lexer::IsDigit(char ch) { return (ch >= 48 && ch <= 57); }
bool radix::Lexer::IsDecimal(char ch) { return (ch == 46); }
bool radix::Lexer::IsParen(char ch) {
  return (ch == 40 || ch == 41 || ch == 91 || ch == 93 || ch == 123 ||
          ch == 125);
}
bool radix::Lexer::StartsWith(std::string src, std::string prefix) {
  return (0 == src.compare(0, prefix.size(), prefix));
}

bool radix::Lexer::HasMatch(std::string token) {
  for (std::map<std::string, std::array<int, 3>>::iterator it =
           operators_.begin();
       it != operators_.end(); ++it) {
    if (StartsWith(it->first, token)) {
      return true;
    }
  }
  for (std::map<std::string, std::array<int, 2>>::iterator it =
           functions_.begin();
       it != functions_.end(); ++it) {
    if (StartsWith(it->first, token)) {
      return true;
    }
  }
  return false;
}

bool radix::Lexer::IsMatch(std::string token) {
  for (std::map<std::string, std::array<int, 3>>::iterator it =
           operators_.begin();
       it != operators_.end(); ++it) {
    if (it->first == token) {
      return true;
    }
  }
  for (std::map<std::string, std::array<int, 2>>::iterator it =
           functions_.begin();
       it != functions_.end(); ++it) {
    if (it->first == token) {
      return true;
    }
  }
  return false;
}

bool radix::Lexer::TokenIsNumeric(std::string token) {
  return (IsDigit(token[0]) || IsDecimal(token[0]));
}
bool radix::Lexer::TokenIsVariable(std::string token) {
  return !(TokenIsNumeric(token) || TokenIsOperator(token) ||
           TokenIsFunction(token) || TokenIsOpenParen(token) ||
           TokenIsCloseParen(token) || token == ",");
}
bool radix::Lexer::TokenIsFunction(std::string token) {
  return (functions_.find(token) != functions_.end());
}
bool radix::Lexer::TokenIsOperator(std::string token) {
  return (operators_.find(token) != operators_.end());
}
bool radix::Lexer::TokenIsOpenParen(std::string token) {
  return (token == "(" || token == "[" || token == "{");
}
bool radix::Lexer::TokenIsCloseParen(std::string token) {
  return (token == ")" || token == "]" || token == "}");
}

std::string radix::Lexer::GetMatching(std::string token) {
  if (token == ")") {
    return "(";
  } else if (token == "]") {
    return "[";
  } else if (token == "}") {
    return "{";
  }
  return "";
}
