#include "function/function.hpp"

#include <cstdlib>

#include "equation/equation.hpp"
#include "equation_base.hpp"

radix::Function::Function()
    : EquationBase(FUNCTION), n_args_(0), n_defaulted_(0) {}
radix::Function::Function(std::size_t n_args, std::size_t n_default)
    : EquationBase(FUNCTION), n_args_(n_args), n_defaulted_(n_default) {}
radix::Function::~Function() {}
