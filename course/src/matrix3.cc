#include "matrix3.h"
#include "vector3.h"

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace ekumen {
namespace math {
namespace {
constexpr int kMatrix3ElementSz = 9;
constexpr int kMatrix3RowSz = 3;

// Returns a stringstream with the format: '[first, second, third]'.
template <class T>
std::ostringstream formatStr(const T& first, const T& second, const T& third) {
  std::ostringstream oss;
  oss << "[" << first << ", " << second << ", " << third << "]";
  return oss;
}

// Formats a string from a Vector3 object with the format: '[x, y, z]'.
std::string formatRow(const Vector3& obj) {
  return formatStr<double>(obj.x(), obj.y(), obj.z()).str();
}

// Checks that the index to access the member rows is in range.
void assertValidAccessIndex(int index) {
  if (index < 0 || index > 2) {
    throw std::invalid_argument(
        "Index to access a row must be in range (0;2).");
  }
}
}  // namespace

const Matrix3 Matrix3::kIdentity = Matrix3({1, 0, 0}, {0, 1, 0}, {0, 0, 1});
const Matrix3 Matrix3::kZero = Matrix3({0, 0, 0}, {0, 0, 0}, {0, 0, 0});
const Matrix3 Matrix3::kOnes = Matrix3({1, 1, 1}, {1, 1, 1}, {1, 1, 1});

Matrix3::Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2)
    : rows_{row0, row1, row2} {}

Matrix3::Matrix3(std::initializer_list<double> matrix) {
  if (matrix.size() != kMatrix3ElementSz) {
    throw std::invalid_argument("Invalid matrix size.");
  }
  for (auto i = 0; i < kMatrix3ElementSz; i += 3) {
    Vector3 row(*(matrix.begin() + i), *(matrix.begin() + i + 1),
                *(matrix.begin() + i + 2));
    rows_.push_back(row);
  }
}

Matrix3 Matrix3::operator+(const Matrix3& obj) const {
  return Matrix3(rows_[0] + obj.row(0), rows_[1] + obj.row(1),
                 rows_[2] + obj.row(2));
}

Matrix3 Matrix3::operator-(const Matrix3& obj) const {
  return Matrix3(rows_[0] - obj.row(0), rows_[1] - obj.row(1),
                 rows_[2] - obj.row(2));
}

Matrix3 Matrix3::operator*(const Matrix3& obj) const {
  return Matrix3(rows_[0] * obj.row(0), rows_[1] * obj.row(1),
                 rows_[2] * obj.row(2));
}

Matrix3 Matrix3::operator*(const double& factor) const {
  return Matrix3(rows_[0] * factor, rows_[1] * factor, rows_[2] * factor);
}

Matrix3 operator*(const double& factor, const Matrix3& obj) {
  return Matrix3(obj.row(0) * factor, obj.row(1) * factor, obj.row(2) * factor);
}

Matrix3 Matrix3::operator/(const Matrix3& obj) const {
  return Matrix3(rows_[0] / obj.row(0), rows_[1] / obj.row(1),
                 rows_[2] / obj.row(2));
}

bool Matrix3::operator==(const Matrix3& rhs) const {
  return (rows_[0] == rhs.row(0) && rows_[1] == rhs.row(1) &&
          rows_[2] == rhs.row(2));
}

const Vector3& Matrix3::operator[](int index) const {
  assertValidAccessIndex(index);
  return rows_[index];
}

Vector3& Matrix3::operator[](int index) {
  assertValidAccessIndex(index);
  return rows_[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix3& obj) {
  os << formatStr<std::string>(formatRow(obj.row(0)), formatRow(obj.row(1)),
                               formatRow(obj.row(2)))
            .str();
  return os;
}

const Vector3& Matrix3::row(int index) const {
  assertValidAccessIndex(index);
  return rows_[index];
}

Vector3 Matrix3::col(int index) {
  return Vector3(rows_[0][index], rows_[1][index], rows_[2][index]);
}

double Matrix3::det() const {
  auto det = 0.;
  for (auto i = 0; i < kMatrix3RowSz; ++i) {
    det += rows_[i % kMatrix3RowSz].x() * rows_[(i + 1) % kMatrix3RowSz].y() *
           rows_[(i + 2) % kMatrix3RowSz].z();
    det -= rows_[i % kMatrix3RowSz].x() * rows_[(i + 2) % kMatrix3RowSz].y() *
           rows_[(i + 1) % kMatrix3RowSz].z();
  }
  return det;
}
}  // namespace math
}  // namespace ekumen
