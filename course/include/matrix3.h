#pragma once

#include <vector>
#include "vector3.h"

namespace ekumen {
namespace math {

// TODO(devitturi): add special member functions to this class.
// TODO(devitturi): add a matrix-product method.
// Represents a 3x3 matrix in the real-domain.
class Matrix3 {
 public:
  // The 3x3 identity matrix;
  static const Matrix3 kIdentity;

  // A 3x3 zero-filled matrix.
  static const Matrix3 kZero;

  // A 3x3 one-filled matrix.
  static const Matrix3 kOnes;

  Matrix3();
  Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);
  Matrix3(std::initializer_list<double> matrix);

  // Member to member addition. Sums the corresponding components of two
  // matrices.
  Matrix3 operator+(const Matrix3& obj) const;

  // Member to member substraction. Substracts the corresponding components of
  // two matrices.
  Matrix3 operator-(const Matrix3& obj) const;

  // Member to member product. Multiplies the corresponding components of two
  // matrices.
  Matrix3 operator*(const Matrix3& obj) const;

  // Scales the matrix by a factor.
  Matrix3 operator*(const double& factor) const;

  // Scales the matrix by a factor.
  friend Matrix3 operator*(const double& factor, const Matrix3& obj);

  // Member to member division. Divides the corresponding components of two
  // matrices.
  Matrix3 operator/(const Matrix3& obj) const;

  bool operator==(const Matrix3& rhs) const;

  const Vector3& operator[](int index) const;
  Vector3& operator[](int index);

  // Serializes the matrix to a stream with the format: '[[a11, a12, a13], [a21,
  // a22, a23], [a31, a32, a33]]'.
  friend std::ostream& operator<<(std::ostream& os, const Matrix3& obj);

  // Gets a row by its index.
  const Vector3& row(int index) const;

  // Gets a column by its index.
  Vector3 col(int index) const;

  // Computes the determinant of the matrix.
  double det() const;

  // Computes the product of two Matrix3.
  Matrix3 Product(const Matrix3& obj) const;

  // Computes the product bewteen a Matrix3 and a Vector3.
  Vector3 Product(const Vector3& obj) const;

  // Computes the product bewteen a Vector3 and a Matrix3.
  friend Vector3 Product(const Vector3& vector, const Matrix3& matrix);

 private:
  // Checks that the index to access the member rows is in range.
  void assertValidAccessIndex(int index) const;

  std::vector<Vector3> rows_;
};

}  // namespace math
}  // namespace ekumen
