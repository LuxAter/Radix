#ifndef RADIX_FUNCTION_HPP_
#define RADIX_FUNCTION_HPP_

#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <memory>
#include <map>

#include "../expression.hpp"

#include "../value/variable.hpp"

namespace radix {
class Function : public Expression {
 public:
  typedef std::vector<std::shared_ptr<Expression>>::reference reference;
  typedef std::vector<std::shared_ptr<Expression>>::const_reference
      const_reference;
  typedef std::vector<std::shared_ptr<Expression>>::pointer pointer;
  typedef std::vector<std::shared_ptr<Expression>>::const_pointer
      const_pointer;
  typedef std::vector<std::shared_ptr<Expression>>::iterator iterator;
  typedef std::vector<std::shared_ptr<Expression>>::const_iterator
      const_iterator;
  typedef std::vector<std::shared_ptr<Expression>>::reverse_iterator
      reverse_iterator;
  typedef std::vector<std::shared_ptr<Expression>>::const_reverse_iterator
      const_reverse_iterator;

  Function();
  Function(const std::string_view& name);
  Function(const char& name);
  virtual ~Function();

  reference front();
  const_reference front() const;
  const_reference cfront() const;
  reference back();
  const_reference back() const;
  const_reference cback() const;

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crbegin() const;
  reverse_iterator rend();
  const_reverse_iterator rend() const;
  const_reverse_iterator crend() const;

  void clear();

  void insert(const_iterator pos, const std::shared_ptr<Expression>& val);
  void erase(const_iterator pos);
  void erase(const_iterator first, const_iterator last);
  void push_back(const std::shared_ptr<Expression>& val);
  void pop_back();

  void AddParam(const std::string_view& ref, std::shared_ptr<Value> val=NULL);
  void AddParam(const char& ref, std::shared_ptr<Value> val=NULL);
  std::shared_ptr<Value>& Param(const std::string_view& ref);
  std::shared_ptr<Value>& Param(const char& ref);

  virtual std::string Latex() const;

  std::shared_ptr<Value> operator()(std::vector<std::shared_ptr<Value>> args);
  // template <typename... Args>
  // void operator()(const Args&... args) {
  //   if (n_args_ < sizeof...(Args) || n_args_ - n_defaulted_ > sizeof...(Args)) {
  //     throw std::invalid_argument("Function " + ref_+ " is not defined for " +
  //                                 std::to_string(sizeof...(Args)) +
  //                                 " arguments.");
  //   }
  //   std::tuple<Args...> arguments(args...);
  // }

 private:
  const std::string ref_;

  std::vector<std::pair<std::string, std::shared_ptr<Value>>> parameters_;

  std::vector<std::shared_ptr<Expression>> expression_;
};
}  // namespace radix

#endif  // RADIX_FUNCTION_HPP_
