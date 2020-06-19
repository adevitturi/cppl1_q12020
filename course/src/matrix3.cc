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
constexpr int kMatrix3ElementSize = 9;
constexpr int kMatrix3RowSize = 3;

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
}  // namespace

const Matrix3 Matrix3::kIdentity = Matrix3({1, 0, 0}, {0, 1, 0}, {0, 0, 1});
const Matrix3 Matrix3::kZero = Matrix3({0, 0, 0}, {0, 0, 0}, {0, 0, 0});
const Matrix3 Matrix3::kOnes = Matrix3({1, 1, 1}, {1, 1, 1}, {1, 1, 1});

Matrix3::Matrix3() : Matrix3(Vector3::kZero, Vector3::kZero, Vector3::kZero) {}

Matrix3::Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2)
    : rows_{row0, row1, row2} {}

Matrix3::Matrix3(const Matrix3& obj)
    : Matrix3(obj.row(0), obj.row(1), obj.row(2)) {}

Matrix3::Matrix3(Matrix3&& obj) : rows_(std::move(obj.rows_)) {}

Matrix3::Matrix3(std::initializer_list<double> matrix) {
  if (matrix.size() != kMatrix3ElementSize) {
    throw std::invalid_argument("Invalid matrix size.");
  }
  for (auto i = 0; i < kMatrix3ElementSize; i += 3) {
    Vector3 row(*(matrix.begin() + i), *(matrix.begin() + i + 1),
                *(matrix.begin() + i + 2));
    rows_.push_back(row);
  }
}

Matrix3& Matrix3::operator=(const Matrix3& obj) {
  rows_ = obj.rows_;
  return *this;
}

Matrix3& Matrix3::operator=(Matrix3&& obj) {
  // The rvalue reference shouldn't be the same as this.
  if (this == &obj) {
    throw std::invalid_argument(
        "rvalue cannot be identity of lvalue in move assignment.");
  }

  rows_ = std::move(obj.rows_);
  return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& obj) const {
  return Matrix3(row(0) + obj.row(0), row(1) + obj.row(1), row(2) + obj.row(2));
}

Matrix3 Matrix3::operator-(const Matrix3& obj) const {
  return Matrix3(row(0) - obj.row(0), row(1) - obj.row(1), row(2) - obj.row(2));
}

Matrix3 Matrix3::operator*(const Matrix3& obj) const {
  return Matrix3(row(0) * obj.row(0), row(1) * obj.row(1), row(2) * obj.row(2));
}

Matrix3 Matrix3::operator*(const double& factor) const {
  return Matrix3(row(0) * factor, row(1) * factor, row(2) * factor);
}

Matrix3 operator*(const double& factor, const Matrix3& obj) {
  return obj * factor;
}

Matrix3 Matrix3::operator/(const Matrix3& obj) const {
  return Matrix3(row(0) / obj.row(0), row(1) / obj.row(1), row(2) / obj.row(2));
}

bool Matrix3::operator==(const Matrix3& rhs) const {
  return (row(0) == rhs.row(0) && row(1) == rhs.row(1) && row(2) == rhs.row(2));
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

Vector3 Matrix3::col(int index) const {
  return Vector3(rows_[0][index], rows_[1][index], rows_[2][index]);
}

double Matrix3::det() const {
  auto det = 0.;
  for (auto i = 0; i < kMatrix3RowSize; ++i) {
    det += rows_[i % kMatrix3RowSize].x() *
           rows_[(i + 1) % kMatrix3RowSize].y() *
           rows_[(i + 2) % kMatrix3RowSize].z();
    det -= rows_[i % kMatrix3RowSize].x() *
           rows_[(i + 2) % kMatrix3RowSize].y() *
           rows_[(i + 1) % kMatrix3RowSize].z();
  }
  return det;
}

Matrix3 Matrix3::product(const Matrix3& obj) const {
  Matrix3 objTranspose(obj.col(0), obj.col(1), obj.col(2));
  Matrix3 res;
  for (auto i = 0; i < kMatrix3RowSize; ++i) {
    for (auto j = 0; j < kMatrix3RowSize; ++j) {
      res[i][j] = row(i).dot(objTranspose.row(j));
    }
  }
  return res;
}

Vector3 Matrix3::product(const Vector3& vector) const {
  Vector3 res;
  for (auto i = 0; i < kMatrix3RowSize; ++i) {
    res[i] = row(i).dot(vector);
  }
  return res;
}

// Checks that the index to access the member rows is in range.
void Matrix3::assertValidAccessIndex(int index) const {
  if (index < 0 || index > 2) {
    throw std::out_of_range("Index to access a row must be in range [0;2].");
  }
}
}  // namespace math
}  // namespace ekumen
