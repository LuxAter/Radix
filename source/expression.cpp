#include "expression.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <tree.hpp>

#include "expression_base.hpp"
#include "lexer.hpp"

std::string Replace(std::string src, std::string match, std::string repl) {
  std::size_t pos = 0;
  while ((pos = src.find(match, pos)) != std::string::npos) {
    src.replace(pos, match.length(), repl);
    pos += repl.length();
  }
  return src;
}

std::string radix::PrintAST(const Expression exp) { return PrintAST(&exp); }

std::string radix::PrintAST(const Expression* exp) {
  std::string ret = exp->node->Unicode(false);
  if (exp->child_size() != 0) {
    ret += '[';
    for (auto it = exp->cchild_begin(); it != exp->cchild_end(); ++it) {
      ret += PrintAST(it.node_);
      if (it != (--exp->cchild_end())) {
        ret += ',';
      }
    }
    ret += ']';
  }
  return ret;
}

std::string radix::PrintDot(const Expression exp) {
  std::vector<std::string> nodes;
  return PrintDot(&exp, nodes);
}
std::string radix::PrintDot(const Expression* exp,
                            std::vector<std::string>& nodes,
                            std::string parent) {
  std::string node = exp->node->Unicode(false);
  std::string repr = node;
  node = Replace(node, "+", "ADD");
  node = Replace(node, "-", "SUB");
  node = Replace(node, "*", "MUL");
  node = Replace(node, "/", "DIV");
  node = Replace(node, "^", "POW");
  node = Replace(node, "%", "MOD");
  node = Replace(node, "!", "FAC");
  node = Replace(node, "()", "");
  node = Replace(node, ".", "DEC");
  std::string ret;
  std::size_t pos = 0;
  while (std::find(nodes.begin(), nodes.end(),
                   parent + node + "_" + std::to_string(pos)) != nodes.end()) {
    pos++;
  }
  ret = "  " + parent + node + "_" + std::to_string(pos) + " [label=\"" + repr +
        "\"]\n";
  nodes.push_back(parent + node + "_" + std::to_string(pos));
  if (parent != std::string()) {
    ret += "  " + parent + " -- " + parent + node + "_" + std::to_string(pos) +
           ";\n";
  }
  for (auto it = exp->cchild_begin(); it != exp->cchild_end(); ++it) {
    ret += PrintDot(it.node_, nodes, parent + node + "_" + std::to_string(pos));
  }
  if (parent == std::string()) {
    ret = "graph expression {\n" + ret + "}";
  }
  return ret;
}

std::string radix::Latex(const Expression exp) { return Latex(&exp); }

std::string radix::Latex(const Expression* exp) {
  std::string ret = exp->node->Latex(true);
  if (exp->child_size() != 0) {
    std::vector<std::string> children;
    for (auto it = exp->cchild_begin(); it != exp->cchild_end(); ++it) {
      children.push_back(Latex(it.node_));
    }
    for (std::size_t i = 0; i < children.size(); ++i) {
      ret = Replace(ret, "$" + std::to_string(i), children.at(i));
    }
  }
  return ret;
}

std::string radix::Unicode(const Expression exp) { return Unicode(&exp); }

std::string radix::Unicode(const Expression* exp) {
  std::string ret = exp->node->Unicode(true);
  if (exp->child_size() != 0) {
    std::vector<std::string> children;
    for (auto it = exp->cchild_begin(); it != exp->cchild_end(); ++it) {
      children.push_back(Unicode(it.node_));
    }
    for (std::size_t i = 0; i < children.size(); ++i) {
      std::size_t pos = 0;
      std::string find_str = "$" + std::to_string(i);
      std::string replace_str = children.at(i);
      while ((pos = ret.find(find_str, pos)) != std::string::npos) {
        ret.replace(pos, find_str.length(), replace_str);
        pos += replace_str.length();
      }
    }
  }
  return ret;
}
