#include "function/function.hpp"

#include <algorithm>
#include <cstdlib>

#include "equation/equation.hpp"
#include "expression.hpp"

radix::Function::Function()
    : Expression(FUNCTION) {}
radix::Function::Function(const std::string_view& name)
    : Expression(FUNCTION), ref_(name) {}
radix::Function::Function(const char& name)
    : Expression(FUNCTION), ref_(1, name) {}
radix::Function::~Function() {}

radix::Function::reference radix::Function::front() {
  return expression_.front();
}
radix::Function::const_reference radix::Function::front() const {
  return expression_.front();
}
radix::Function::const_reference radix::Function::cfront() const {
  return expression_.front();
}
radix::Function::reference radix::Function::back() {
  return expression_.back();
}
radix::Function::const_reference radix::Function::back() const {
  return expression_.back();
}
radix::Function::const_reference radix::Function::cback() const {
  return expression_.back();
}

radix::Function::iterator radix::Function::begin() {
  return expression_.begin();
}
radix::Function::const_iterator radix::Function::begin() const {
  return expression_.cbegin();
}
radix::Function::const_iterator radix::Function::cbegin() const {
  return expression_.cbegin();
}
radix::Function::iterator radix::Function::end() { return expression_.end(); }
radix::Function::const_iterator radix::Function::end() const {
  return expression_.cend();
}
radix::Function::const_iterator radix::Function::cend() const {
  return expression_.cend();
}
radix::Function::reverse_iterator radix::Function::rbegin() {
  return expression_.rbegin();
}
radix::Function::const_reverse_iterator radix::Function::rbegin() const {
  return expression_.crbegin();
}
radix::Function::const_reverse_iterator radix::Function::crbegin() const {
  return expression_.crbegin();
}
radix::Function::reverse_iterator radix::Function::rend() {
  return expression_.rend();
}
radix::Function::const_reverse_iterator radix::Function::rend() const {
  return expression_.crend();
}
radix::Function::const_reverse_iterator radix::Function::crend() const {
  return expression_.crend();
}

void radix::Function::clear() { expression_.clear(); }

void radix::Function::insert(const_iterator pos,
                             const std::shared_ptr<Expression>& val) {
  expression_.insert(pos, val);
}
void radix::Function::erase(const_iterator pos) { expression_.erase(pos); }
void radix::Function::erase(const_iterator first, const_iterator last) {
  expression_.erase(first, last);
}
void radix::Function::push_back(const std::shared_ptr<Expression>& val) {
  expression_.push_back(val);
}
void radix::Function::pop_back() { expression_.pop_back(); }

void radix::Function::AddParam(const std::string_view& ref,
                               std::shared_ptr<Value> val) {
  std::string ref_str(ref);
  std::vector<std::pair<std::string, std::shared_ptr<Value>>>::iterator it =
      std::find_if(
          parameters_.begin(), parameters_.end(),
          [&](const std::pair<std::string, std::shared_ptr<Value>>& element) {
            return element.first == ref_str;
          });
  if (it == parameters_.end()) {
    parameters_.push_back(
        std::pair<std::string, std::shared_ptr<Value>>(ref_str, val));
  } else {
    it->second = val;
  }
}
void radix::Function::AddParam(const char& ref, std::shared_ptr<Value> val) {
  std::string ref_str(1, ref);
  std::vector<std::pair<std::string, std::shared_ptr<Value>>>::iterator it =
      std::find_if(
          parameters_.begin(), parameters_.end(),
          [&](const std::pair<std::string, std::shared_ptr<Value>>& element) {
            return element.first == ref_str;
          });
  if (it == parameters_.end()) {
    parameters_.push_back(
        std::pair<std::string, std::shared_ptr<Value>>(ref_str, val));
  } else {
    it->second = val;
  }
}

std::shared_ptr<radix::Value>& radix::Function::Param(
    const std::string_view& ref) {
  std::string ref_str(ref);
  std::vector<std::pair<std::string, std::shared_ptr<Value>>>::iterator it =
      std::find_if(
          parameters_.begin(), parameters_.end(),
          [&](const std::pair<std::string, std::shared_ptr<Value>>& element) {
            return element.first == ref_str;
          });
  if (it == parameters_.end()) {
    throw std::invalid_argument(ref_str + " is not a valid parameter for " +
                                ref_);
  } else {
    return it->second;
  }
}

std::shared_ptr<radix::Value>& radix::Function::Param(const char& ref) {
  std::string ref_str(1, ref);
  std::vector<std::pair<std::string, std::shared_ptr<Value>>>::iterator it =
      std::find_if(
          parameters_.begin(), parameters_.end(),
          [&](const std::pair<std::string, std::shared_ptr<Value>>& element) {
            return element.first == ref_str;
          });
  if (it == parameters_.end()) {
    throw std::invalid_argument(ref_str + " is not a valid parameter for " +
                                ref_);
  } else {
    return it->second;
  }
}

std::string radix::Function::Latex() const {
  std::string repr = ref_ + "\\left(";
  for (auto& it : parameters_) {
    repr += it.first;
    if (it.second != NULL) {
      repr += "=" + it.second->Latex();
    }
    if (it != *(--parameters_.end())) {
      repr += ", ";
    }
  }
  repr += "\\right) = ";
  for (auto& it : expression_) {
    repr += it->Latex();
  }
  return repr;
}

std::shared_ptr<radix::Value> radix::Function::operator()(
    std::vector<std::shared_ptr<Value>> args_) {
  std::vector<std::shared_ptr<Value>> args;
  if(args.size() < parameters_.size()){
    for(auto it = parameters_.begin() + args.size(); it != parameters_.end(); ++it){

    }
  }
}
