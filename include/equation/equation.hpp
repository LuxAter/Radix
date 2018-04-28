#ifndef RADIX_EQUATION_HPP_
#define RADIX_EQUATION_HPP_

#include <memory>
#include <vector>

#include "../expression.hpp"

namespace radix {
class Equation : public Expression {
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

  Equation();
  virtual ~Equation();

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

  virtual std::string Latex() const;

 private:
  std::vector<std::shared_ptr<Expression>> components_;
};

std::ostream& operator<<(std::ostream& out, const Equation& lhs);

// Comparison Operators
// ============================================================================
bool operator==(const Equation& lhs, const Equation& rhs);
bool operator!=(const Equation& lhs, const Equation& rhs);
bool operator<(const Equation& lhs, const Equation& rhs);
bool operator>(const Equation& lhs, const Equation& rhs);
bool operator<=(const Equation& lhs, const Equation& rhs);
bool operator>=(const Equation& lhs, const Equation& rhs);

// Arithmetic Operators
// ============================================================================
Equation operator+(const Equation& lhs, const Equation& rhs);
Equation operator-(const Equation& lhs, const Equation& rhs);
Equation operator*(const Equation& lhs, const Equation& rhs);
Equation operator/(const Equation& lhs, const Equation& rhs);

}  // namespace radix

#endif  // RADIX_EQUATION_HPP_
