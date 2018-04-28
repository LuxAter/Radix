#include "value/variable.hpp"

#include <memory>
#include <string>
#include <ostream>

#include "value/value.hpp"

radix::Variable::Variable() : Value(VARIABLE), ref_(), val_(NULL) {}
radix::Variable::Variable(const std::string& ref_str)
    : Value(VARIABLE), ref_(ref_str), val_(NULL) {}
radix::Variable::Variable(const char& ref_ch)
    : Value(VARIABLE), ref_(1, ref_ch), val_(NULL) {}
radix::Variable::~Variable() {}

void radix::Variable::SetRef(const std::string& ref_str) { ref_ = ref_str; }
void radix::Variable::SetRef(const char& ref_ch) { ref_ = ref_ch; }
void radix::Variable::SetVal(std::shared_ptr<Value> val) { val_ = val; }

std::string radix::Variable::GetRef() const { return ref_; }
std::shared_ptr<radix::Value> radix::Variable::GetVal() const { return val_; }

radix::Variable& radix::Variable::operator=(const std::shared_ptr<Value> val){
  val_ = val;
  return *this;
}

std::ostream& radix::operator<<(std::ostream& out, const Variable& lhs){
  if (lhs.GetVal() == NULL){
    out << lhs.GetRef();
  }else{
    out << lhs.GetVal();
  }
  return out;
}
