#ifndef RADIX_VALUE_VARIABLE_HPP_
#define RADIX_VALUE_VARIABLE_HPP_

#include "value.hpp"

#include <memory>
#include <ostream>
#include <string>

namespace radix {
class Variable : public Value {
 public:
  Variable();
  explicit Variable(const std::string& ref_str);
  explicit Variable(const char& ref_ch);
  explicit Variable(const std::string& ref_str, std::shared_ptr<Value> val);
  explicit Variable(const char& ref_ch, std::shared_ptr<Value> val);
  virtual ~Variable();

  void SetRef(const std::string& ref_str);
  void SetRef(const char& ref_ch);
  void SetVal(std::shared_ptr<Value> val);

  std::string GetRef() const;
  std::shared_ptr<Value> GetVal() const;

  virtual std::string Latex(bool recurse = true) const;
  // virtual std::string Tree(std::size_t indent = 2) const;

  Variable& operator=(const std::shared_ptr<Value> val);

  operator std::shared_ptr<Value>();
  operator std::shared_ptr<ExpressionBase>();

 private:
  std::string ref_;
  std::shared_ptr<Value> val_;
};

std::ostream& operator<<(std::ostream& out, const Variable& lhs);

std::shared_ptr<Value> operator+(const Variable& lhs, const Variable& rhs);
std::shared_ptr<Value> operator-(const Variable& lhs, const Variable& rhs);
std::shared_ptr<Value> operator*(const Variable& lhs, const Variable& rhs);
std::shared_ptr<Value> operator/(const Variable& lhs, const Variable& rhs);

bool operator==(const Variable& lhs, const Variable& rhs);
bool operator!=(const Variable& lhs, const Variable& rhs);
bool operator<(const Variable& lhs, const Variable& rhs);
bool operator>(const Variable& lhs, const Variable& rhs);
bool operator<=(const Variable& lhs, const Variable& rhs);
bool operator>=(const Variable& lhs, const Variable& rhs);

typedef Variable var;

}  // namespace radix

#endif  // RADIX_VALUE_VARIABLE_HPP_
