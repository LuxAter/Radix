#ifndef RADIX_PLOT_PLOT_CLASS_HPP_
#define RADIX_PLOT_PLOT_CLASS_HPP_

#include <limits>
#include <string>
#include <vector>

#include "../log.hpp"

namespace radix {
namespace plot {
  class Figure {
   public:
    Figure();

    inline void grid() { grid_ = !grid_; }

    void plot(std::vector<double> x_data, std::vector<double> y_data,
              std::string style = "");
    void scatter(std::vector<double> x_data, std::vector<double> y_data,
                 std::string style = "");

    void imshow(std::vector<std::vector<double>> data,
                double v_min = -std::numeric_limits<double>::infinity(),
                double v_max = std::numeric_limits<double>::infinity(),
                std::string style = "");

    std::string title;
    std::string xlabel, ylabel;
    std::array<double, 2> xlim, ylim;
    std::array<double, 4> margins;

   protected:
    bool grid_ = false;

   private:
  };
}  // namespace plot
}  // namespace radix

#endif  // RADIX_PLOT_PLOT_CLASS_HPP_
