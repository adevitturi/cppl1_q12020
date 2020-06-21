#include "isometry.h"
#include <cmath>
#include "matrix3.h"
#include "vector3.h"

namespace ekumen {
namespace math {
namespace {}  // namespace

Isometry::Isometry(const Vector3& translation, const Matrix3& rotation)
    : translation_(translation), rotation_(rotation) {}

Isometry::Isometry(const Matrix3& rotation)
    : translation_(Vector3::kZero), rotation_(rotation) {}

Isometry::Isometry(const Isometry& obj)
    : Isometry(obj.translation_, obj.rotation_) {}

Isometry::Isometry(Isometry&& obj)
    : translation_(std::move(obj.translation_)),
      rotation_(std::move(obj.rotation_)) {}

Isometry& Isometry::operator=(const Isometry& obj) {
  translation_ = obj.translation_;
  rotation_ = obj.rotation_;
  return *this;
}
Isometry& Isometry::operator=(Isometry&& obj) {
  // The rvalue reference shouldn't be the same as this.
  if (this == &obj) {
    throw std::invalid_argument(
        "rvalue cannot be identity of lvalue in move assignment.");
  }

  translation_ = std::move(obj.translation_);
  rotation_ = std::move(obj.rotation_);
  return *this;
}

Isometry Isometry::FromTranslation(const Vector3& translation) {
  return Isometry(translation);
}

Isometry Isometry::RotateAround(const Vector3& axis, const double& angle) {
  Matrix3 res(Matrix3::kIdentity);
  double cosAngle = std::cos(angle);
  double sinAngle = std::sin(angle);
  if (axis == Vector3::kUnitX) {
    res[1][1] = cosAngle;
    res[1][2] = -1 * sinAngle;
    res[2][1] = sinAngle;
    res[2][2] = cosAngle;
  } else if (axis == Vector3::kUnitY) {
    res[0][0] = cosAngle;
    res[0][2] = sinAngle;
    res[2][0] = -1 * sinAngle;
    res[2][2] = cosAngle;
  } else if (axis == Vector3::kUnitZ) {
    res[0][0] = cosAngle;
    res[0][1] = -1 * sinAngle;
    res[1][0] = sinAngle;
    res[1][1] = cosAngle;
  } else {
    throw std::invalid_argument(
        "Axis to rotate around should be a unitary versor.");
  }
  return Isometry(res);
}

Isometry Isometry::FromEulerAngles(const double& psi, const double& theta,
                                   const double& phi) {
  Isometry psi_rotation = Isometry::RotateAround(Vector3::kUnitX, psi);
  Isometry theta_rotation = Isometry::RotateAround(Vector3::kUnitY, theta);
  Isometry phi_rotation = Isometry::RotateAround(Vector3::kUnitZ, phi);
  return psi_rotation * theta_rotation * phi_rotation;
}

Matrix3 Isometry::rotation() const { return rotation_; }
Vector3 Isometry::translation() const { return translation_; }

Isometry Isometry::operator*(const Isometry& obj) const {
  double res_translation_x =
      rotation_.row(0).dot(obj.translation_) + translation_.x();
  double res_translation_y =
      rotation_.row(1).dot(obj.translation_) + translation_.y();
  double res_translation_z =
      rotation_.row(2).dot(obj.translation_) + translation_.z();

  Vector3 res_translation(res_translation_x, res_translation_y,
                          res_translation_z);

  Matrix3 res_rotation = rotation_.product(obj.rotation_);

  return Isometry(res_translation, res_rotation);
}

Vector3 Isometry::operator*(const Vector3& obj) const {
  Vector3 res = rotation_.product(obj) + translation_;
  return res;
}

bool Isometry::operator==(const Isometry& rhs) const {
  return translation_ == rhs.translation_ && rotation_ == rhs.rotation_;
}

bool Isometry::operator!=(const Isometry& rhs) const { return !(*this == rhs); }

std::ostream& operator<<(std::ostream& os, const Isometry& obj) {
  os << "[T: " << obj.translation() << ", R:" << obj.rotation() << "]";
  return os;
}

Vector3 Isometry::transform(const Vector3& obj) const { return *this * obj; }

Isometry Isometry::compose(const Isometry& obj) const { return *this * obj; }

Isometry Isometry::inverse() const {
  Matrix3 inverse_rotation = rotation_.inverse();
  return Isometry(inverse_rotation.product(translation_) * (-1),
                  inverse_rotation);
}

}  // namespace math
}  // namespace ekumen
