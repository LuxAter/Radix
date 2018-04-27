#ifndef RADIX_EQUATION_BASE_HPP_
#define RADIX_EQUATION_BASE_HPP_

namespace radix {
  enum EquationType {
    EQUATION = 0,
    CONSTANT = 1
  };

  class EquationBase{
    public:
      EquationBase();
      EquationBase(const EquationType& type);
      virtual ~EquationBase();

      EquationType type_;

    private:
  };
} // namespace radix

#endif  // RADIX_EQUATION_BASE_HPP_
