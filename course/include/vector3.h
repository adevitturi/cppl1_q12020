#pragma once

#include <initializer_list>
#include <iostream>
#include <vector>

namespace ekumen {
namespace math {

// Represents a three dimensional vector in the real-domain.
class Vector3 {
 public:
  // Unitary versor in the x axis.
  static const Vector3 kUnitX;

  // Unitary versor in the y axis.
  static const Vector3 kUnitY;

  // Unitary versor in the z axis.
  static const Vector3 kUnitZ;

  // Zero-filled vector.
  static const Vector3 kZero;

  explicit Vector3(const double& x = 0, const double& y = 0,
                   const double& z = 0);
  Vector3(const Vector3& obj);
  Vector3(Vector3&& obj);
  Vector3(std::initializer_list<double> vector);
  ~Vector3();

  Vector3& operator=(const Vector3& obj);

  Vector3& operator=(Vector3&& obj);

  // Member to member addition. Sums the corresponding components of two
  // vectors.
  Vector3 operator+(const Vector3& obj) const;

  // Member to member substraction. Substracts the corresponding components of
  // two vectors.
  Vector3 operator-(const Vector3& obj) const;

  // Member to member product. Multiplies the corresponding components of two
  // vectors.
  Vector3 operator*(const Vector3& obj) const;

  // Scales the vector to a factor.
  Vector3 operator*(const double& factor) const;

  // Scales the vector to a factor.
  friend Vector3 operator*(const double& factor, const Vector3& obj);

  // Member to member division. Divides the corresponding components of two
  // vectors.
  Vector3 operator/(const Vector3& obj) const;

  // Scales the vector dividing it by a factor.
  Vector3 operator/(const double& factor) const;

  bool operator==(const Vector3& rhs) const;
  bool operator!=(const Vector3& rhs) const;

  // Access vector components. Use [0] for x axis, [1] for y axis, [2] for z
  // axis.
  const double& operator[](int index) const;
  double& operator[](int index);

  // Serializes the vector to a stream with the format: '(x: a, y: b, z: c)'.
  friend std::ostream& operator<<(std::ostream& os, const Vector3& obj);

  const double& x() const;
  double& x();
  const double& y() const;
  double& y();
  const double& z() const;
  double& z();

  // Gets the vector's module.
  double norm() const;

  // Computes the dot product between two vectors.
  double dot(const Vector3& obj) const;

  // Computes the cross product between two vectors.
  Vector3 cross(const Vector3& obj) const;

 private:
  // Checks that the index to access the vector components is in range.
  void assertValidAccessIndex(int index) const;

  double* elem_;
};

}  // namespace math
}  // namespace ekumen
