#pragma once

class Vector {
 public:
  constexpr Vector() noexcept;
  constexpr Vector(double ix, double iy, double iz) noexcept;
  constexpr Vector& operator=(const Vector& other) noexcept;

 public:
  alignas(32) double vec4[4];

 public:
  double& x = vec4[0];
  double& y = vec4[1];
  double& z = vec4[2];
  double& w = vec4[3];
};

constexpr Vector::Vector() noexcept : Vector(0.0, 0.0, 0.0) {}

constexpr Vector::Vector(double ix, double iy, double iz) noexcept
    : vec4{ix, iy, iz, 0.0} {}

constexpr Vector& Vector::operator=(const Vector& other) noexcept {
  vec4[0] = other.vec4[0];
  vec4[1] = other.vec4[1];
  vec4[2] = other.vec4[2];
  vec4[3] = other.vec4[3];
  return *this;
}
