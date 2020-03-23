#pragma once

class Point {
 public:
  constexpr Point();
  constexpr Point(double ix, double iy, double iz);

 public:
  alignas(32) double vec4[4];

 public:
  double& x = vec4[0];
  double& y = vec4[1];
  double& z = vec4[2];
  double& w = vec4[3];
};

constexpr Point::Point() : Point(0.0, 0.0, 0.0) {}

constexpr Point::Point(double ix, double iy, double iz)
    : vec4{ix, iy, iz, 1.0} {}
