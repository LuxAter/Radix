#ifndef RADIX_VALUE_VARIABLE_HPP_
#define RADIX_VALUE_VARIABLE_HPP_

#include "value.hpp"

#include <string>
#include <memory>
#include <ostream>

namespace radix {
class Variable : public Value {
 public:
  Variable();
  explicit Variable(const std::string& ref_str);
  explicit Variable(const char& ref_ch);
  virtual ~Variable();

  void SetRef(const std::string& ref_str);
  void SetRef(const char& ref_ch);
  void SetVal(std::shared_ptr<Value> val);

  std::string GetRef() const;
  std::shared_ptr<Value> GetVal() const;

  Variable& operator=(const std::shared_ptr<Value> val);

 private:
  std::string ref_;
  std::shared_ptr<Value> val_;
};

std::ostream& operator<<(std::ostream& out, const Variable& lhs);

}  // namespace radix

#endif  // RADIX_VALUE_VARIABLE_HPP_
