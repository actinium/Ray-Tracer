#pragma once

class Point {
 public:
  constexpr Point() noexcept;
  constexpr Point(double ix, double iy, double iz) noexcept;
  constexpr Point& operator=(const Point& other) noexcept;

 public:
  alignas(32) double vec4[4];

 public:
  double& x = vec4[0];
  double& y = vec4[1];
  double& z = vec4[2];
  double& w = vec4[3];
};

constexpr Point::Point() noexcept : Point(0.0, 0.0, 0.0) {}

constexpr Point::Point(double ix, double iy, double iz) noexcept
    : vec4{ix, iy, iz, 1.0} {}

constexpr Point& Point::operator=(const Point& other) noexcept {
  vec4[0] = other.vec4[0];
  vec4[1] = other.vec4[1];
  vec4[2] = other.vec4[2];
  vec4[3] = other.vec4[3];
  return *this;
}
