#include "value/long.hpp"

#include <mpfr.h>
#include <stdio.h>
#include <cstring>

#include <ostream>
#include <string>
#include <memory>

#include "value/value.hpp"

radix::Long::Long() : Value(INT) {
  SetPrecision(sizeof(int) * 8);
  mpfr_set_si(value_, 0.0, MPFR_RNDD);
}
radix::Long::Long(int val) : Value(INT) {
  SetPrecision(sizeof(int) * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(long int val) : Value(INT) {
  SetPrecision(sizeof(long) * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(long long int val) : Value(INT) {
  SetPrecision(sizeof(long long) * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned int val) : Value(INT) {
  SetPrecision(sizeof(unsigned) * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned long int val) : Value(INT) {
  SetPrecision(sizeof(unsigned long) * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned long long int val) : Value(INT) {
  SetPrecision(sizeof(unsigned long long) * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(float val) : Value(INT) {
  SetPrecision(sizeof(float) * 8);
  mpfr_set_flt(value_, val, MPFR_RNDD);
}
radix::Long::Long(double val) : Value(INT) {
  SetPrecision(sizeof(float) * 8);
  mpfr_set_d(value_, val, MPFR_RNDD);
}
radix::Long::Long(long double val) : Value(INT) {
  SetPrecision(sizeof(float) * 8);
  mpfr_set_ld(value_, val, MPFR_RNDD);
}
radix::Long::Long(std::string val) : Value(INT) {
  SetPrecision(val.size() * sizeof(char) * 8);
  mpfr_set_str(value_, val.c_str(), val.size(), MPFR_RNDD);
}
radix::Long::Long(const char* val) : Value(INT) {
  SetPrecision(std::strlen(val) * sizeof(char) * 8);
  mpfr_set_str(value_, val, 10, MPFR_RNDD);
}
radix::Long::Long(int val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(long int val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(long long int val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned int val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned long int val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned long long int val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(float val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_flt(value_, val, MPFR_RNDD);
}
radix::Long::Long(double val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_d(value_, val, MPFR_RNDD);
}
radix::Long::Long(long double val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_ld(value_, val, MPFR_RNDD);
}
radix::Long::Long(std::string val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_str(value_, val.c_str(), val.size(), MPFR_RNDD);
}
radix::Long::Long(const char* val, std::size_t prec) : Value(INT) {
  SetPrecision(prec * 8);
  mpfr_set_str(value_, val, 10, MPFR_RNDD);
}

radix::Long::Long(const Long& copy) : Value(INT) {
  mpfr_init2(value_, mpfr_get_prec(copy.value_));
  mpfr_set(value_, copy.value_, MPFR_RNDD);
}

radix::Long::~Long() { mpfr_clear(value_); }

void radix::Long::Set(int val) { mpfr_set_si(value_, val, MPFR_RNDD); }
void radix::Long::Set(long int val) { mpfr_set_si(value_, val, MPFR_RNDD); }
void radix::Long::Set(long long int val) {
  mpfr_set_si(value_, val, MPFR_RNDD);
}
void radix::Long::Set(unsigned int val) { mpfr_set_ui(value_, val, MPFR_RNDD); }
void radix::Long::Set(unsigned long int val) {
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
void radix::Long::Set(unsigned long long int val) {
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
void radix::Long::Set(float val) { mpfr_set_flt(value_, val, MPFR_RNDD); }
void radix::Long::Set(double val) { mpfr_set_d(value_, val, MPFR_RNDD); }
void radix::Long::Set(long double val) { mpfr_set_ld(value_, val, MPFR_RNDD); }
void radix::Long::Set(std::string val) {
  mpfr_set_str(value_, val.c_str(), val.size(), MPFR_RNDD);
}
void radix::Long::Set(const char* val) {
  mpfr_set_str(value_, val, std::strlen(val), MPFR_RNDD);
}
void radix::Long::Set(const Long& copy) {
  mpfr_init2(value_, mpfr_get_prec(copy.value_));
  mpfr_set(value_, copy.value_, MPFR_RNDD);
}

void radix::Long::Data(mpfr_t& val) const { mpfr_set(val, value_, MPFR_RNDD); }

std::size_t radix::Long::GetPrecision() const { return mpfr_get_prec(value_); }
void radix::Long::SetPrecision(std::size_t bits) {
  mpfr_init2(value_, bits + 1);
}

std::string radix::Long::GetString(int prec, bool left) const {
  std::string fmt = "%." + std::to_string(prec) + "Rg";
  if (prec == -1) {
    fmt = "%RYg";
  }
  int len = mpfr_snprintf(NULL, 0, fmt.c_str(), value_);
  char* buffer = static_cast<char*>(malloc(len));
  mpfr_snprintf(buffer, len + 1, fmt.c_str(), value_);
  std::string str(buffer, len);
  if (prec != -1 && str.size() < static_cast<std::size_t>(prec)) {
    if (left == true) {
      return (str + std::string(prec - str.size() + 1, ' '));
    } else {
      return (std::string(prec - str.size() + 1, ' ') + str);
    }
  }
  return str;
}

std::string radix::Long::Latex() const {
  return GetString();
}

radix::Long& radix::Long::operator=(int val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(long int val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(long long int val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(unsigned int val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(unsigned long int val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(unsigned long long int val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(float val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(double val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(long double val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(std::string val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(const char* val) {
  Set(val);
  return *this;
}
radix::Long& radix::Long::operator=(const Long& val) {
  Set(val);
  return *this;
}

radix::Long& radix::Long::operator+=(const Long& rhs) {
  mpfr_add(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}
radix::Long& radix::Long::operator-=(const Long& rhs) {
  mpfr_sub(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}
radix::Long& radix::Long::operator*=(const Long& rhs) {
  mpfr_mul(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}
radix::Long& radix::Long::operator/=(const Long& rhs) {
  mpfr_div(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}

radix::Long::operator std::shared_ptr<radix::Value>(){
  return std::dynamic_pointer_cast<radix::Value>(std::make_shared<Long>(*this));
}
radix::Long::operator std::shared_ptr<radix::Expression>(){
  return std::dynamic_pointer_cast<radix::Expression>(std::make_shared<Long>(*this));
}

std::ostream& radix::operator<<(std::ostream& out, const Long& lhs) {
  out << lhs.GetString();
  return out;
}

bool radix::operator==(const Long& lhs, const Long& rhs) {
  return mpfr_equal_p(lhs.value_, rhs.value_);
}
bool radix::operator!=(const Long& lhs, const Long& rhs) {
  return !(lhs == rhs);
}
bool radix::operator<(const Long& lhs, const Long& rhs) {
  return mpfr_less_p(lhs.value_, rhs.value_);
}
bool radix::operator>(const Long& lhs, const Long& rhs) { return rhs < lhs; }
bool radix::operator<=(const Long& lhs, const Long& rhs) {
  return !(rhs < rhs);
}
bool radix::operator>=(const Long& lhs, const Long& rhs) {
  return !(lhs < rhs);
}

radix::Long radix::operator+(const Long& lhs, const Long& rhs) {
  Long res;
  res.SetPrecision(std::min(lhs.GetPrecision(), rhs.GetPrecision()));
  mpfr_add(res.value_, lhs.value_, rhs.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::operator-(const Long& lhs, const Long& rhs) {
  Long res;
  res.SetPrecision(std::min(lhs.GetPrecision(), rhs.GetPrecision()));
  mpfr_sub(res.value_, lhs.value_, rhs.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::operator*(const Long& lhs, const Long& rhs) {
  Long res;
  res.SetPrecision(std::min(lhs.GetPrecision(), rhs.GetPrecision()));
  mpfr_mul(res.value_, lhs.value_, rhs.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::operator/(const Long& lhs, const Long& rhs) {
  Long res;
  res.SetPrecision(std::min(lhs.GetPrecision(), rhs.GetPrecision()));
  mpfr_div(res.value_, lhs.value_, rhs.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::abs(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_abs(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::fabs(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_abs(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::max(const Long& x, const Long& y) {
  Long res;
  res.SetPrecision(std::max(x.GetPrecision(), y.GetPrecision()));
  mpfr_max(res.value_, x.value_, y.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::min(const Long& x, const Long& y) {
  Long res;
  res.SetPrecision(std::min(x.GetPrecision(), y.GetPrecision()));
  mpfr_min(res.value_, x.value_, y.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::exp(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_exp(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::exp2(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_exp2(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::exp10(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_exp10(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::expm1(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_expm1(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::log(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_log(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::log2(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_log2(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::log10(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_log10(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::log1p(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_log1p(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::pow(const Long& base, const Long& exp) {
  Long res;
  res.SetPrecision(base.GetPrecision());
  mpfr_pow(res.value_, base.value_, exp.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::sqrt(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_sqrt(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::cbrt(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_cbrt(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::rootn(const Long& arg, const unsigned long int k) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_root(res.value_, arg.value_, k, MPFR_RNDD);
  return res;
}
radix::Long radix::hypot(const Long& x, const Long& y) {
  Long res;
  res.SetPrecision(std::max(x.GetPrecision(), y.GetPrecision()));
  mpfr_hypot(res.value_, x.value_, y.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::sin(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_sin(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::cos(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_cos(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::tan(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_tan(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::sec(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_sec(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::csc(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_csc(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::cot(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_cot(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::acos(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_acos(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::asin(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_asin(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::atan(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_atan(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::atan2(const Long& y, const Long& x) {
  Long res;
  res.SetPrecision(std::max(y.GetPrecision(), x.GetPrecision()));
  mpfr_atan2(res.value_, y.value_, x.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::sinh(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_sinh(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::cosh(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_cosh(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::tanh(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_tanh(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::sech(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_sech(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::csch(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_csch(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::coth(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_coth(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::acosh(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_acosh(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::asinh(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_asinh(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::atanh(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_atanh(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::erf(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_erf(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::erfc(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_erfc(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::tgamma(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_gamma(res.value_, arg.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::lgamma(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_lngamma(res.value_, arg.value_, MPFR_RNDD);
  return res;
}

radix::Long radix::ceil(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_ceil(res.value_, arg.value_);
  return res;
}
radix::Long radix::floor(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_floor(res.value_, arg.value_);
  return res;
}
radix::Long radix::trunc(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_trunc(res.value_, arg.value_);
  return res;
}
radix::Long radix::round(const Long& arg) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_round(res.value_, arg.value_);
  return res;
}
radix::Long radix::rint(const Long& arg, const RoundingMode& rnd) {
  Long res;
  res.SetPrecision(arg.GetPrecision());
  mpfr_rint(res.value_, arg.value_, static_cast<mpfr_rnd_t>(rnd));
  return res;
}
