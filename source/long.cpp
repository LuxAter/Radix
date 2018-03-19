#include "long.hpp"

// #include <cstdio>
#include <mpfr.h>
#include <stdio.h>
#include <cstring>

#include <ostream>
#include <string>

radix::Long::Long() {
  SetPrecision(sizeof(int) * 8);
  mpfr_set_si(value_, 0.0, MPFR_RNDD);
}
radix::Long::Long(int val) {
  SetPrecision(sizeof(int) * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(long int val) {
  SetPrecision(sizeof(long) * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(long long int val) {
  SetPrecision(sizeof(long long) * 8);
  mpfr_set_si(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned int val) {
  SetPrecision(sizeof(unsigned) * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned long int val) {
  SetPrecision(sizeof(unsigned long) * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(unsigned long long int val) {
  SetPrecision(sizeof(unsigned long long) * 8);
  mpfr_set_ui(value_, val, MPFR_RNDD);
}
radix::Long::Long(float val) {
  SetPrecision(sizeof(float) * 8);
  mpfr_set_flt(value_, val, MPFR_RNDD);
}
radix::Long::Long(double val) {
  SetPrecision(sizeof(float) * 8);
  mpfr_set_d(value_, val, MPFR_RNDD);
}
radix::Long::Long(long double val) {
  SetPrecision(sizeof(float) * 8);
  mpfr_set_ld(value_, val, MPFR_RNDD);
}
radix::Long::Long(std::string val) {
  SetPrecision(val.size() * sizeof(char) * 8);
  mpfr_set_str(value_, val.c_str(), val.size(), MPFR_RNDD);
}
radix::Long::Long(const char* val) {
  SetPrecision(std::strlen(val) * sizeof(char) * 8);
  mpfr_set_str(value_, val, 10, MPFR_RNDD);
}

radix::Long::Long(const Long& copy) {
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

std::size_t radix::Long::GetPrecision() const{
  return mpfr_get_prec(value_);
}
void radix::Long::SetPrecision(std::size_t bits) {
  mpfr_init2(value_, bits + 1);
}

std::string radix::Long::GetString(int prec) const {
  std::string fmt = "%." + std::to_string(prec) + "Rg";
  if (prec == -1) {
    fmt = "%RYg";
  }
  int len = mpfr_snprintf(NULL, 0, fmt.c_str(), value_);
  char* buffer = static_cast<char*>(malloc(len));
  mpfr_snprintf(buffer, len, fmt.c_str(), value_);
  return std::string(buffer, len);
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

radix::Long& radix::Long::operator+=(const Long& rhs){
  mpfr_add(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}
radix::Long& radix::Long::operator-=(const Long& rhs){
  mpfr_sub(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}
radix::Long& radix::Long::operator*=(const Long& rhs){
  mpfr_mul(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
}
radix::Long& radix::Long::operator/=(const Long& rhs){
  mpfr_div(value_, value_, rhs.value_, MPFR_RNDD);
  return *this;
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

radix::Long radix::sqrt(const Long& lhs) {
  Long res;
  res.SetPrecision(lhs.GetPrecision());
  mpfr_sqrt(res.value_, lhs.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::cbrt(const Long& lhs) {
  Long res;
  res.SetPrecision(lhs.GetPrecision());
  mpfr_cbrt(res.value_, lhs.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::rootn(const Long& lhs, const unsigned long int rhs) {
  Long res;
  res.SetPrecision(lhs.GetPrecision());
  mpfr_root(res.value_, lhs.value_, rhs, MPFR_RNDD);
  return res;
}

radix::Long radix::pow(const Long& lhs, const Long& rhs){
  Long res;
  res.SetPrecision(lhs.GetPrecision());
  mpfr_pow(res.value_, lhs.value_, rhs.value_, MPFR_RNDD);
  return res;
}
radix::Long radix::abs(const Long& lhs){
  Long res;
  res.SetPrecision(lhs.GetPrecision());
  mpfr_abs(res.value_, lhs.value_, MPFR_RNDD);
  return res;
}
