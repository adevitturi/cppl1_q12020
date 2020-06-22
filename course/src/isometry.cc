#include "isometry.h"
#include <cmath>
#include "matrix3.h"
#include "vector3.h"

namespace ekumen {
namespace math {
namespace {
constexpr int kMatrix3RowSize = 3;
}  // namespace.

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
  if (this == &obj) {
    return *this;
  }

  translation_ = std::move(obj.translation_);
  rotation_ = std::move(obj.rotation_);
  return *this;
}

Isometry Isometry::FromTranslation(const Vector3& translation) {
  return Isometry(translation);
}

Isometry Isometry::RotateAround(const Vector3& axis, const double& angle) {
  Matrix3 res;
  Vector3 axis_norm;

  if (axis.norm() != 1) {
    axis_norm = axis / axis.norm();
  } else {
    axis_norm = axis;
  }
  const double cos_angle = std::cos(angle);
  const double sin_angle = std::sin(angle);
  const double cos_complement = 1 - cos_angle;
  const double x = axis_norm.x();
  const double y = axis_norm.y();
  const double z = axis_norm.z();

  res[0][0] = x * x * cos_complement + cos_angle;
  res[0][1] = x * y * cos_complement - z * sin_angle;
  res[0][2] = x * z * cos_complement + y * sin_angle;

  res[1][0] = y * x * cos_complement + z * sin_angle;
  res[1][1] = y * y * cos_complement + cos_angle;
  res[1][2] = y * z * cos_complement - x * sin_angle;

  res[2][0] = z * x * cos_complement - y * sin_angle;
  res[2][1] = z * y * cos_complement + x * sin_angle;
  res[2][2] = z * z * cos_complement + cos_angle;

  return Isometry(res);
}

Isometry Isometry::FromEulerAngles(const double& psi, const double& theta,
                                   const double& phi) {
  const Isometry psi_rotation = Isometry::RotateAround(Vector3::kUnitX, psi);
  const Isometry theta_rotation =
      Isometry::RotateAround(Vector3::kUnitY, theta);
  const Isometry phi_rotation = Isometry::RotateAround(Vector3::kUnitZ, phi);
  return psi_rotation * theta_rotation * phi_rotation;
}

const Matrix3& Isometry::rotation() const { return rotation_; }
const Vector3& Isometry::translation() const { return translation_; }

Isometry Isometry::operator*(const Isometry& obj) const {
  const Vector3 res_translation =
      rotation_.product(obj.translation_) + translation_;
  const Matrix3 res_rotation = rotation_.product(obj.rotation_);
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
  const Matrix3 inverse_rotation = rotation_.inverse();
  return Isometry(inverse_rotation.product(translation_) * (-1),
                  inverse_rotation);
}

}  // namespace math
}  // namespace ekumen
