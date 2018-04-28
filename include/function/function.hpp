#ifndef RADIX_FUNCTION_HPP_
#define RADIX_FUNCTION_HPP_

#include "../equation_base.hpp"

#include "../equation/equation.hpp"

#include <cstdlib>
#include <stdexcept>

namespace radix {
class Function : public EquationBase {
 public:
  Function();
  Function(std::size_t n_args, std::size_t n_default);
  virtual ~Function();

  template <typename... Args>
  void operator()(const Args&... args) {
    if (n_args_ < sizeof...(Args) || n_args_ - n_defaulted_ > sizeof...(Args)) {
      throw std::invalid_argument("Function " + name_ + " is not defined for " +
                                  std::to_string(sizeof...(Args)) +
                                  " arguments.");
    }
    std::tuple<Args...> arguments(args...);
  }

 private:
  const std::string name_;
  const std::size_t n_args_, n_defaulted_;

  Equation eqation_;
};
}  // namespace radix

#endif  // RADIX_FUNCTION_HPP_
