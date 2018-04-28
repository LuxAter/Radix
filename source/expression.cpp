#include "expression.hpp"

radix::Expression::Expression() {}
radix::Expression::Expression(const ExpressionType& type) : type_(type) {}
radix::Expression::~Expression() {}

std::string radix::Expression::Latex() const { return "EQB"; }
