#pragma once

namespace ekumen {
namespace math {

class DoubleUtil {
 public:
  // Compares 'a' and 'b' according to the desired precision in units in the
  // last place (ULPs).
  static bool compare(const double& a, const double& b, const int& ulp);

 private:
};

}  // namespace math
}  // namespace ekumen
