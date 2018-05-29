#include "parser/latex.hpp"

#include <algorithm>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include <iostream>

#include "expression.hpp"
// #include "estl/tree.hpp"

std::string ReplaceAll(std::string str, const std::string& from,
                       const std::string& to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos +=
        to.length();  // Handles case where 'to' is a substring of 'from'
  }
  return str;
}

std::size_t SplitToken(std::string token){
  std::size_t pos = 0, prev = 0;
  pos = token.find_first_not_of("0123456789.", pos);
  prev = pos;
  while(pos != 0 && pos != std::string::npos){
    prev = pos;
    pos = token.find_first_not_of("0123456789.", pos + 1);
  }
  if(prev == 0){
    prev = std::string::npos;
  }
  return prev;
}

std::shared_ptr<radix::Expression> radix::ParseLatex(std::string exp) {
  std::shared_ptr<Expression> result =
      std::make_shared<Expression>(Expression());
  std::vector<std::pair<std::string, std::string>> replacements = {
      {",", " "},   {"(", " ( "}, {")", " ) "}, {"+", " + "},
      {"-", " - "}, {"/", " / "}, {"*", " * "}, {"^", " ^ "}};
  for (auto& it : replacements) {
    exp = ReplaceAll(exp, it.first, it.second);
  }
  std::stringstream iss(exp);
  std::vector<std::string> input{std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}};
  for(std::size_t i = 0; i != input.size(); ++i){
    std::size_t pos = SplitToken(input[i]);
    if(pos != std::string::npos && pos != 0){
      std::string pre = input[i].substr(0, pos);
      std::string post = input[i].substr(pos);
      input[i] = post;
      input.insert(input.begin() + i, "*");
      input.insert(input.begin() + i, pre);
      i += 2;
    }
  }
  std::vector<std::string> tokens;
  // estl::tree::Tree<std::string> ast;
  std::vector<std::string> functions = {"sin", "cos", "tan", "log", "pow"};
  std::map<std::string, int> precedence = {
      {"^", 4}, {"*", 3}, {"/", 3}, {"+", 2}, {"-", 2}};
  std::map<std::string, bool> left_assoc = {
      {"^", false}, {"*", true}, {"/", true}, {"+", true}, {"-", true}};
  std::stack<std::pair<std::string, int>> operator_stack;
  for (auto& it : input) {
    if (precedence.find(it) != precedence.end()) {
      while (operator_stack.size() != 0 &&
             (operator_stack.top().second == -1 ||
              operator_stack.top().second > precedence[it] ||
              (operator_stack.top().second == precedence[it] &&
               left_assoc[operator_stack.top().first])) &&
             operator_stack.top().first != "(") {
        tokens.push_back(operator_stack.top().first);
        operator_stack.pop();
      }
      operator_stack.push({it, precedence[it]});
    } else if (it == "(") {
      operator_stack.push({"(", 0});
    } else if (it == ")") {
      while (operator_stack.size() != 0 && operator_stack.top().first != "(") {
        tokens.push_back(operator_stack.top().first);
        operator_stack.pop();
      }
      operator_stack.pop();
    } else if (std::find(functions.begin(), functions.end(), it) !=
               functions.end()) {
      operator_stack.push({it, -1});
    } else {
      tokens.push_back(it);
    }
  }
  while (operator_stack.size() != 0) {
    tokens.push_back(operator_stack.top().first);
    operator_stack.pop();
  }
  for (auto& it : tokens) {
    std::cout << it << ' ';
  }
  return result;
}
