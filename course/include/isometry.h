#ifndef ISOMETRY_H
#define ISOMETRY_H

#include "matrix3.h"
#include "vector3.h"

namespace ekumen {
namespace math {

// TODO(devitturi): add special member functions to this class.
// Represents an Homogeneous matrix to perform isometry transformations.
class Isometry {
 public:
  explicit Isometry(const Vector3& translation = Vector3::kZero,
                    const Matrix3& rotation = Matrix3::kIdentity);
  explicit Isometry(const Matrix3& rotation);

  // Returns an isometry transformation from a pure translation.
  static Isometry FromTranslation(const Vector3& translation);

  // Returns an isometry transformation from a pure rotation around an axis.
  static Isometry RotateAround(const Vector3& axis, const double& angle);

  // Returns an isometry transformation from a pure rotation around Euler angles
  // (in the x-y-z or pitch-roll-yaw convention).
  static Isometry FromEulerAngles(const double& psi, const double& theta,
                                  const double& phi);

  // Gets the rotation matrix.
  Matrix3 rotation() const;

  // Gets the translation vector.
  Vector3 translation() const;

  // Composes two isometry transformations.
  Isometry operator*(const Isometry& obj) const;

  // Transforms a 3-cordinate point with the curent transformation represented
  // by this object.
  Vector3 operator*(const Vector3& obj) const;

  // Compares two isometry objects for equality.
  bool operator==(const Isometry& rhs) const;

  // Compares two isometry objects for inequality.
  bool operator!=(const Isometry& rhs) const;

  // Serializes the isometry to a stream with the format: "[T: (x, y, z),
  // R:[[a11, a12, a21], [a21, a22, a23], [a31, a32, a33]]]"
  friend std::ostream& operator<<(std::ostream& os, const Isometry& obj);

  // Transforms a 3-cordinate point with the curent transformation represented
  // by this object.
  Vector3 transform(const Vector3& obj) const;

  // Composes two isometry transformations.
  Isometry compose(const Isometry& obj) const;

  // Gets the inverse transformation to this isometry object.
  Isometry inverse() const;

 private:
  Vector3 translation_;
  Matrix3 rotation_;
};

}  // namespace math
}  // namespace ekumen
#endif
