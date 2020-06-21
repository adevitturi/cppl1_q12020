// This file describes a challenge of a C++ L1 Padawan. The goal
// of this unit test is to suggest an API and the abstractions
// needed to implement an isometry.

// Consider including other header files if needed.
#include "isometry.h"
#include "matrix3.h"
#include "vector3.h"

#include <cmath>
// #include <sstream>
// #include <string>

#include "gtest/gtest.h"

namespace ekumen {
namespace math {
namespace test {
namespace {
constexpr double kTolerance{1e-12};
}  // namespace

GTEST_TEST(IsometryTest, Accessors) {
  Isometry t1 = Isometry::FromTranslation({1., 2., 3.});
  Isometry t2{{1., 2., 3.}, Matrix3::kIdentity};
  EXPECT_EQ(t1, t2);
  EXPECT_EQ(t1.rotation(), Matrix3::kIdentity);
  EXPECT_EQ(t1.translation(), Vector3(1, 2, 3));
}

GTEST_TEST(IsometryTest, IsometryOperations) {
  const Isometry t1 = Isometry::FromTranslation({1., 2., 3.});
  const Isometry t2{{1., 2., 3.}, Matrix3::kIdentity};
  EXPECT_EQ(t1 * Vector3(1., 1., 1.), Vector3(2., 3., 4.));
  EXPECT_EQ(t1.transform({1., 1., 1.}), Vector3(2., 3., 4.));
  EXPECT_EQ(t1.inverse() * Vector3(2., 3., 4.), Vector3(1., 1., 1.));
  EXPECT_EQ(t1 * t2 * Vector3(1., 1., 1.), Vector3(3., 5., 7.));
  EXPECT_EQ(t1.compose(t2) * Vector3(1., 1., 1.), Vector3(3., 5., 7.));
}

GTEST_TEST(IsometryTest, ComposedRotations) {
  const Isometry t3{Isometry::RotateAround(Vector3::kUnitX, M_PI / 2.)};
  const Isometry t4{Isometry::RotateAround(Vector3::kUnitY, M_PI / 4.)};
  const Isometry t5{Isometry::RotateAround(Vector3::kUnitZ, M_PI / 8.)};
  const Isometry t6{Isometry::FromEulerAngles(M_PI / 2., M_PI / 4., M_PI / 8.)};
  EXPECT_EQ(t6, t3 * t4 * t5);
  EXPECT_EQ(t3.translation(), Vector3::kZero);
  const double pi_8{M_PI / 8.};
  const double cpi_8{std::cos(pi_8)};  // 0.923879532
  const double spi_8{std::sin(pi_8)};  // 0.382683432
  EXPECT_EQ(t5.rotation(),
            Matrix3({cpi_8, -spi_8, 0., spi_8, cpi_8, 0., 0., 0., 1.}));
}

GTEST_TEST(IsometryTest, Serialize) {
  const Isometry t5{Isometry::RotateAround(Vector3::kUnitZ, M_PI / 8.)};
  std::stringstream ss;
  ss << t5;
  EXPECT_EQ(ss.str(),
            "[T: (x: 0, y: 0, z: 0), R:[[0.923879533, -0.382683432, 0], "
            "[0.382683432, 0.923879533, 0], [0, 0, 1]]]");
}

}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
