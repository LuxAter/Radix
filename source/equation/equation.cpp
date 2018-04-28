#include "equation/equation.hpp"
#include "equation_base.hpp"

#include <memory>
#include <vector>

radix::Equation::Equation() : EquationBase(EQUATION) {}
radix::Equation::~Equation() {}

radix::Equation::reference radix::Equation::front() {
  return components_.front();
}
radix::Equation::const_reference radix::Equation::front() const {
  return components_.front();
}
radix::Equation::const_reference radix::Equation::cfront() const {
  return components_.front();
}
radix::Equation::reference radix::Equation::back() {
  return components_.back();
}
radix::Equation::const_reference radix::Equation::back() const {
  return components_.back();
}
radix::Equation::const_reference radix::Equation::cback() const {
  return components_.back();
}

radix::Equation::iterator radix::Equation::begin() {
  return components_.begin();
}
radix::Equation::const_iterator radix::Equation::begin() const {
  return components_.cbegin();
}
radix::Equation::const_iterator radix::Equation::cbegin() const {
  return components_.cbegin();
}
radix::Equation::iterator radix::Equation::end() { return components_.end(); }
radix::Equation::const_iterator radix::Equation::end() const {
  return components_.cend();
}
radix::Equation::const_iterator radix::Equation::cend() const {
  return components_.cend();
}
radix::Equation::reverse_iterator radix::Equation::rbegin() {
  return components_.rbegin();
}
radix::Equation::const_reverse_iterator radix::Equation::rbegin() const {
  return components_.crbegin();
}
radix::Equation::const_reverse_iterator radix::Equation::crbegin() const {
  return components_.crbegin();
}
radix::Equation::reverse_iterator radix::Equation::rend() {
  return components_.rend();
}
radix::Equation::const_reverse_iterator radix::Equation::rend() const {
  return components_.crend();
}
radix::Equation::const_reverse_iterator radix::Equation::crend() const {
  return components_.crend();
}

void radix::Equation::clear() { components_.clear(); }

void radix::Equation::insert(const_iterator pos,
                             const std::shared_ptr<EquationBase>& val) {
  components_.insert(pos, val);
}
void radix::Equation::erase(const_iterator pos) { components_.erase(pos); }
void radix::Equation::erase(const_iterator first, const_iterator last) {
  components_.erase(first, last);
}
void radix::Equation::push_back(const std::shared_ptr<EquationBase>& val) {
  components_.push_back(val);
}
void radix::Equation::pop_back() { components_.pop_back(); }
