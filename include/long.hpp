#ifndef RADIX_LONG_HPP_
#define RADIX_LONG_HPP_

#include <mpfr.h>

#include <ostream>
#include <string>

namespace radix {
class Long {
 public:
  Long();
  Long(int val);
  Long(long int val);
  Long(long long int val);
  Long(unsigned int val);
  Long(unsigned long int val);
  Long(unsigned long long int val);
  Long(float val);
  Long(double val);
  Long(long double val);
  Long(std::string val);
  Long(const char* val);

  Long(const Long& copy);

  virtual ~Long();

  void Set(int val);
  void Set(long int val);
  void Set(long long int val);
  void Set(unsigned int val);
  void Set(unsigned long int val);
  void Set(unsigned long long int val);
  void Set(float val);
  void Set(double val);
  void Set(long double val);
  void Set(std::string val);
  void Set(const char* val);
  void Set(const Long& copy);

  void Data(mpfr_t& val) const;

  std::size_t GetPrecision() const;
  void SetPrecision(std::size_t bits);

  std::string GetString(int prec=-1) const;

  Long& operator=(int val);
  Long& operator=(long int val);
  Long& operator=(long long int val);
  Long& operator=(unsigned int val);
  Long& operator=(unsigned long int val);
  Long& operator=(unsigned long long int val);
  Long& operator=(float val);
  Long& operator=(double val);
  Long& operator=(long double val);
  Long& operator=(std::string val);
  Long& operator=(const char* val);
  Long& operator=(const Long& val);

  Long& operator+=(const Long& rhs);
  Long& operator-=(const Long& rhs);
  Long& operator*=(const Long& rhs);
  Long& operator/=(const Long& rhs);

  mpfr_t value_;

 private:

};

std::ostream& operator<<(std::ostream& out, const Long& lhs);

bool operator==(const Long& lhs, const Long& rhs);
bool operator!=(const Long& lhs, const Long& rhs);
bool operator<(const Long& lhs, const Long& rhs);
bool operator>(const Long& lhs, const Long& rhs);
bool operator<=(const Long& lhs, const Long& rhs);
bool operator>=(const Long& lhs, const Long& rhs);

Long operator+(const Long& lhs, const Long& rhs);
Long operator-(const Long& lhs, const Long& rhs);
Long operator*(const Long& lhs, const Long& rhs);
Long operator/(const Long& lhs, const Long& rhs);

Long sqrt(const Long& lhs);
Long cbrt(const Long& lhs);
Long rootn(const Long& lhs, const unsigned long int rhs);
Long pow(const Long& lhs, const Long& rhs);
Long abs(const Long& lhs);

}  // namespace radix

#endif  // RADIX_LONG_HPP_
