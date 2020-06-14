#include "matrix3.h"
#include "gtest/gtest.h"
#include "vector3.h"

namespace ekumen {
namespace math {
namespace test {

namespace {
constexpr double kTolerance{1e-12};
}  // namespace

Matrix3 m1{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
Matrix3 m2{1., 2., 3., 4., 5., 6., 7., 8., 9.};

GTEST_TEST(Matrix3Test, Constructors) { EXPECT_EQ(m1, m2); }

GTEST_TEST(Matrix3Test, Accessors) {
  EXPECT_EQ(m1.row(0), Vector3(1., 2., 3.));
  EXPECT_EQ(m1.col(1), Vector3(2., 5., 8.));
  EXPECT_EQ(m1[1], Vector3(4., 5., 6.));
  EXPECT_EQ(m1[2][1], 8.);

  const std::vector<Vector3> kExpectedRows{
      Vector3(1., 2., 3.), Vector3(4., 5., 6.), Vector3(7., 8., 9.)};
  const std::vector<Vector3> kExpectedCols{
      Vector3(1., 4., 7.), Vector3(2., 5., 8.), Vector3(3., 6., 9.)};
  for (const Vector3& r : kExpectedRows) {
    bool found{false};
    for (int i = 0; i < 3; ++i) {
      if (r == m2.row(i)) {
        found = true;
        break;
      }
    }
    ASSERT_TRUE(found);
  }
  for (const Vector3& c : kExpectedCols) {
    bool found{false};
    for (int i = 0; i < 3; ++i) {
      if (c == m2.col(i)) {
        found = true;
        break;
      }
    }
    ASSERT_TRUE(found);
  }
}

GTEST_TEST(Matrix3Test, AccesorOutOfRange) {
  ASSERT_THROW(m2.row(5), std::out_of_range);
  ASSERT_THROW(m2.row(6), std::out_of_range);
  ASSERT_THROW(m2.col(8), std::out_of_range);
}

GTEST_TEST(Matrix3Test, Operations) {
  EXPECT_EQ(m1, m2);
  EXPECT_EQ(m1 - m2, Matrix3::kZero);
  EXPECT_EQ(m1 + m2, m1 * 2.);
  EXPECT_EQ(m1 + m2, 2. * m2);
  EXPECT_EQ(m1 * m2, ((std ::initializer_list<double>){1., 4., 9., 16., 25.,
                                                       36., 49., 64., 81.}));
  EXPECT_EQ(m1 / m2, Matrix3::kOnes);
}

GTEST_TEST(Matrix3Test, Serialize) {
  const Matrix3 m3 = Matrix3::kIdentity;
  std::stringstream ss;
  ss << m3;
  EXPECT_EQ(ss.str(), "[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
}

GTEST_TEST(Matrix3Test, Determinant) {
  EXPECT_NEAR(m1.det(), 0., kTolerance);
  m1[2][2] = 10.;
  EXPECT_NEAR(m1.det(), -2.9999999999999996, kTolerance);
}

}  // namespace test
}  // namespace math
}  // namespace ekumen

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
