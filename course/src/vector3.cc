#include "vector3.h"
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace ekumen {
namespace math {
namespace {
constexpr double square(double x) { return x * x; }
constexpr auto kVectorSize = 3;
}  // namespace

const Vector3 Vector3::kUnitX = Vector3(1, 0, 0);
const Vector3 Vector3::kUnitY = Vector3(0, 1, 0);
const Vector3 Vector3::kUnitZ = Vector3(0, 0, 1);
const Vector3 Vector3::kZero = Vector3(0, 0, 0);

Vector3::Vector3(const double& x, const double& y, const double& z)
    : elem_{new double[kVectorSize]} {
  elem_[0] = x;
  elem_[1] = y;
  elem_[2] = z;
}

Vector3::Vector3(const Vector3& obj) : Vector3(obj.x(), obj.y(), obj.z()) {}

Vector3::Vector3(Vector3&& obj) : elem_{obj.elem_} { obj.elem_ = nullptr; }

Vector3::Vector3(std::initializer_list<double> vector) {
  if (vector.size() != kVectorSize) {
    throw std::invalid_argument("Invalid vector size.");
  }
  elem_ = new double[kVectorSize];
  for (auto i = 0; i < kVectorSize; ++i) {
    elem_[i] = vector.begin()[i];
  }
}

Vector3::~Vector3() { delete[] elem_; }

Vector3& Vector3::operator=(const Vector3& obj) {
  for (auto i = 0; i < kVectorSize; ++i) {
    elem_[i] = obj[i];
  }
  return *this;
}

Vector3& Vector3::operator=(Vector3&& obj) {
  elem_ = obj.elem_;
  obj.elem_ = nullptr;
  return *this;
}

Vector3 Vector3::operator+(const Vector3& obj) const {
  return Vector3(x() + obj.x(), y() + obj.y(), z() + obj.z());
}

Vector3 Vector3::operator-(const Vector3& obj) const {
  return Vector3(x() - obj.x(), y() - obj.y(), z() - obj.z());
}

Vector3 Vector3::operator*(const Vector3& obj) const {
  return Vector3(x() * obj.x(), y() * obj.y(), z() * obj.z());
}

Vector3 Vector3::operator*(const double& factor) const {
  return Vector3(x() * factor, y() * factor, z() * factor);
}

Vector3 operator*(const double& factor, const Vector3& obj) {
  return Vector3(factor * obj.x(), factor * obj.y(), factor * obj.z());
}

Vector3 Vector3::operator/(const Vector3& obj) const {
  return Vector3(x() / obj.x(), y() / obj.y(), z() / obj.z());
}

Vector3 Vector3::operator/(const double& factor) const {
  return Vector3(x() / factor, y() / factor, z() / factor);
}

bool Vector3::operator==(const Vector3& rhs) const {
  return (x() == rhs.x() && y() == rhs.y() && z() == rhs.z());
}

bool Vector3::operator!=(const Vector3& rhs) const { return !(*this == rhs); }

const double& Vector3::operator[](int index) const {
  assertValidAccessIndex(index);
  return elem_[index];
}

double& Vector3::operator[](int index) {
  assertValidAccessIndex(index);
  return elem_[index];
}

std::ostream& operator<<(std::ostream& os, const Vector3& obj) {
  os << "(x: " << obj.x() << ", y: " << obj.y() << ", z: " << obj.z() << ")";
  return os;
}

double Vector3::norm() const {
  return std::sqrt(square(x()) + square(y()) + square(z()));
}

double Vector3::dot(const Vector3& obj) const {
  double result = 0;
  for (auto i = 0; i < kVectorSize; ++i) {
    result += elem_[i] * obj[i];
  }
  return result;
}

Vector3 Vector3::cross(const Vector3& obj) const {
  auto res_x = this->y() * obj.z() - this->z() * obj.y();
  auto res_y = this->z() * obj.x() - this->x() * obj.z();
  auto res_z = this->x() * obj.y() - this->y() * obj.x();
  return Vector3(res_x, res_y, res_z);
}

const double& Vector3::x() const { return elem_[0]; }

// Try avoiding using this. This is error-prone as it can have two
// responsibilities as getter or setter.
double& Vector3::x() { return elem_[0]; }

const double& Vector3::y() const { return elem_[1]; }

// Try avoiding using this. This is error-prone as it can have two
// responsibilities as getter or setter.
double& Vector3::y() { return elem_[1]; }

const double& Vector3::z() const { return elem_[2]; }

// Try avoiding using this. This is error-prone as it can have two
// responsibilities as getter or setter.
double& Vector3::z() { return elem_[2]; }

void Vector3::assertValidAccessIndex(int index) const {
  if (index < 0 || index > 2) {
    throw std::out_of_range(
        "Index to access an element must be in range (0;2).");
  }
}

}  // namespace math
}  // namespace ekumen
