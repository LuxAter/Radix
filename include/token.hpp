#ifndef RADIX_TOKEN_HPP_
#define RADIX_TOKEN_HPP_

#include <string>
#include <iostream>

namespace radix {
class Token {
 public:

   enum Type{
     NONE = 0,
     CONST = 1,
     EQUALITY = 2,
     VARIABLE = 3,
     FUNCTION = 4
   };

  Token();
  virtual ~Token();

  void SetType(Type type);
  void SetConst(long double constant);

  Type GetType() const;
  long double GetConst() const;

  std::string GetRepr() const;

 private:
  Type type_;
  long double const_;
  std::string repr_;
};

inline bool operator==(const radix::Token& lhs, radix::Token& rhs);
std::ostream& operator<<(std::ostream& out, const radix::Token& lhs);

}  // namespace radix

#endif  // RADIX_TOKEN_HPP_
