#include "lexer.hpp"

#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include <logger.hpp>
#include <tree.hpp>

#include "expression_base.hpp"

#include "function/function.hpp"
#include "function/operator.hpp"

#include "value/long.hpp"
#include "value/variable.hpp"


radix::Lexer::Lexer() {}
radix::Lexer::~Lexer() {}

estl::tree::Tree<std::shared_ptr<radix::ExpressionBase>> radix::Lexer::Parse(
    std::string exp) {
  std::queue<std::pair<std::string, TokenType>> token_queue =
      GetTokenQueue(exp);
  std::stack<estl::tree::Tree<std::shared_ptr<ExpressionBase>>> tree_stack;
  std::stack<estl::tree::Tree<std::string>> string_stack;
  while (token_queue.size() != 0) {
    std::pair<std::string, TokenType> token = token_queue.front();
    if (token.second == NUMERIC) {
      tree_stack.push(
          estl::tree::Tree<std::shared_ptr<ExpressionBase>>(Long(token.first)));
      string_stack.push(estl::tree::Tree<std::string>(token.first));
    } else if (token.second == VARIABLE) {
      tree_stack.push(estl::tree::Tree<std::shared_ptr<ExpressionBase>>(
          Variable(token.first)));
      string_stack.push(estl::tree::Tree<std::string>(token.first));
    } else if (token.second == FUNCTION) {
      estl::tree::Tree<std::shared_ptr<ExpressionBase>> func(
          Function(token.first));
      estl::tree::Tree<std::string> sfunc(token.first);
      for (int i = 0; i < functions_[token.first][1]; ++i) {
        func.prepend(tree_stack.top());
        tree_stack.pop();
        sfunc.prepend(string_stack.top());
        string_stack.pop();
      }
      tree_stack.push(func);
      string_stack.push(sfunc);
    } else if (token.second == OPERATOR) {
      estl::tree::Tree<std::shared_ptr<ExpressionBase>> op(
          Operator(token.first));
      estl::tree::Tree<std::string> sop(token.first);
      for (int i = 0; i < operators_[token.first][1]; ++i) {
        op.prepend(tree_stack.top());
        tree_stack.pop();
        sop.prepend(string_stack.top());
        string_stack.pop();
      }
      tree_stack.push(op);
      string_stack.push(sop);
    }
    token_queue.pop();
  }
  // std::cout << string_stack.top() << "<<\n";
  return tree_stack.top();
}

std::queue<std::pair<std::string, radix::Lexer::TokenType>>
radix::Lexer::GetTokenQueue(std::string exp) {
  expression_ = exp;
  pos_ = 0;
  std::queue<std::pair<std::string, TokenType>> token_queue;
  std::stack<std::pair<std::string, TokenType>> operator_stack;
  std::pair<std::string, TokenType> token;
  while (token.first != "EOS") {
    token = GetNextToken();
    if (token.first == "EOS") {
      break;
    }
    if (token.second == NUMERIC || token.second == VARIABLE) {
      token_queue.push(token);
    } else if (token.second == FUNCTION) {
      operator_stack.push(token);
    } else if (token.second == OPERATOR) {
      while (operator_stack.size() != 0 &&
             operator_stack.top().second != OPEN_PAREN &&
             (operator_stack.top().second == FUNCTION ||
              operators_[operator_stack.top().first][0] >
                  operators_[token.first][0] ||
              (operators_[operator_stack.top().first][0] ==
                   operators_[token.first][0] &&
               !operators_[operator_stack.top().first][2]))) {
        token_queue.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.push(token);

    } else if (token.second == OPEN_PAREN) {
      operator_stack.push(token);
    } else if (token.second == CLOSE_PAREN) {
      std::string matching = GetMatching(token.first);
      while (operator_stack.top().first != matching) {
        if (operator_stack.top().second == OPEN_PAREN) {
          estl::logger::Error("Unclosed parentheses block");
        }
        token_queue.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
    } else if (token.first == ",") {
      while (operator_stack.top().second != OPEN_PAREN) {
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

std::pair<std::string, radix::Lexer::TokenType> radix::Lexer::GetNextToken() {
  if (pos_ >= expression_.size()) {
    return {"EOS", EOS};
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
      } else if (current == ',') {
        local++;
        res += current;
        break;
      }
    } else if (pos_ + local == expression_.size()) {
      break;
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
      } else if (current == ',') {
        break;
      } else if (is_num && !IsDigit(current)) {
        expression_.insert(expression_.begin() + pos_ + local, '&');
        break;
      }
    }
    res += current;
    local++;
  }
  pos_ += local;
  if (TokenIsNumeric(res)) {
    return {res, NUMERIC};
  } else if (TokenIsVariable(res)) {
    return {res, VARIABLE};
  } else if (TokenIsFunction(res)) {
    return {res, FUNCTION};
  } else if (TokenIsOperator(res)) {
    return {res, OPERATOR};
  } else if (TokenIsOpenParen(res)) {
    return {res, OPEN_PAREN};
  } else if (TokenIsCloseParen(res)) {
    return {res, CLOSE_PAREN};
  }
  return {res, EOS};
}

void radix::Lexer::LoadOperators() {
  operators_["+"] = {2, 2, 1};
  operators_["-"] = {2, 2, 1};
  operators_["*"] = {3, 2, 1};
  operators_["&"] = {5, 2, 1};
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
  for(auto it : fmap){
    functions_[it.second.first] = {-1, static_cast<int>(it.second.second)};
  }
}

void radix::Lexer::AddOperator(std::string op, int prec, int nargs){
  operators_[op] = {prec, nargs, 1};
}
void radix::Lexer::AddFunction(std::string func, int nargs){
  functions_[func] = {-1, nargs};
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
