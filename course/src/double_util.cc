#include "double_util.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>

namespace ekumen {
namespace math {
bool DoubleUtil::compare(const double& a, const double& b, const int& ulp) {
  // the machine epsilon has to be scaled to the magnitude of the values used
  // and multiplied by the desired precision in ULPs (units in the last place)
  return std::fabs(a - b) <=
             std::numeric_limits<double>::epsilon() * std::fabs(a + b) * ulp
         // unless the result is subnormal
         || std::fabs(a - b) < std::numeric_limits<double>::min();
}
}  // namespace math
}  // namespace ekumen
