#include "vector3.h"
#include "gtest/gtest.h"

namespace ekumen {
namespace math {
namespace test {

namespace {
constexpr double kTolerance{1e-12};
}  // namespace

const Vector3 p(1., 2., 3.);
const Vector3 q{4., 5., 6.};

GTEST_TEST(Vector3Test, Accessors) {
  EXPECT_EQ(p.x(), 1);
  EXPECT_EQ(p.y(), 2);
  EXPECT_EQ(p.z(), 3);
  EXPECT_EQ(p[0], 1.);
  EXPECT_EQ(p[1], 2.);
  EXPECT_EQ(p[2], 3.);

  Vector3 t;
  t.x() = 1.;
  t[1] = 2.;
  t.z() = 3.;
  EXPECT_EQ(t, p);
}

GTEST_TEST(Vector3Test, MoveAssignment) {
  Vector3 v;
  ASSERT_THROW(v = std::move(v), std::invalid_argument);
}

GTEST_TEST(Vector3Test, AccesorOutOfRange) {
  ASSERT_THROW(p[5], std::out_of_range);
}

GTEST_TEST(Vector3Test, Operations) {
  EXPECT_EQ(p + q, ((std::initializer_list<double>){5., 7., 9.}));
  EXPECT_EQ(p - q, ((std::initializer_list<double>){-3., -3., -3.}));
  EXPECT_EQ(p * 2., Vector3(2., 4., 6));
  EXPECT_EQ(p / 2., Vector3(0.5, 1, 1.5));
  EXPECT_EQ(2 * q, Vector3(8., 10., 12.));
  EXPECT_EQ(p * q, Vector3(4., 10., 18.));
  EXPECT_EQ(p / q, Vector3(.25, .4, .5));
  EXPECT_TRUE(p != q);
  EXPECT_FALSE(p == q);
}

GTEST_TEST(Vector3Test, Norm) {
  EXPECT_NEAR(p.norm(), 3.7416573867739413, kTolerance);
}

GTEST_TEST(Vector3Test, Serialize) {
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "(x: 1, y: 2, z: 3)");
}

GTEST_TEST(Vector3Test, StaticConstMembers) {
  EXPECT_TRUE(Vector3::kUnitX == Vector3(1., 0., 0));
  EXPECT_TRUE(Vector3::kUnitX != ((std::initializer_list<double>){1., 1., 0}));

  EXPECT_TRUE(Vector3::kUnitY == Vector3(0, 1., 0));
  EXPECT_TRUE(Vector3::kUnitY == ((std::initializer_list<double>){0., 1., 0}));

  EXPECT_TRUE(Vector3::kUnitZ == Vector3(0, 0., 1));
}

GTEST_TEST(Vector3Test, DotProduct) {
  const Vector3 r(3., 2., 1.);
  EXPECT_NEAR(p.dot(r), 10, kTolerance);
  EXPECT_NEAR(Vector3::kUnitX.dot(Vector3::kUnitZ), 0., kTolerance);
}

GTEST_TEST(Vector3Test, CrossProduct) {
  const Vector3 r(3., 2., 1.);
  const Vector3 expected_res(-4, 8, -4);
  EXPECT_TRUE(p.cross(r) == expected_res);
  EXPECT_TRUE(Vector3::kUnitZ == Vector3::kUnitX.cross(Vector3::kUnitY));
}

GTEST_TEST(Vector3Test, InitNoArgs) {
  Vector3 t;
  EXPECT_EQ(t, Vector3::kZero);
}

}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
