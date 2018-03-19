#include "token.hpp"

#include <string>
#include <sstream>
#include <iostream>

radix::Token::Token() {}

radix::Token::~Token() {}

void radix::Token::SetType(Type type) { type_ = type; }
void radix::Token::SetConst(long double constant) { const_ = constant; }

radix::Token::Type radix::Token::GetType() const { return type_; }
long double radix::Token::GetConst() const { return const_; }

std::string radix::Token::GetRepr() const {
  if(type_ == CONST){
    printf("%.50Lf\n", const_);
    return std::to_string(const_);
  }else{
    return repr_;
  }
}

bool radix::operator==(const radix::Token& lhs, radix::Token& rhs) {
  return (lhs.GetType() == rhs.GetType());
}

std::ostream& radix::operator<<(std::ostream& out, const radix::Token& lhs){
  out << lhs.GetRepr();
  return out;
}
