#pragma once

class Point {
 public:
  constexpr Point();
  constexpr Point(double ix, double iy, double iz);

 public:
  alignas(32) double v[4];

 public:
  double& x = v[0];
  double& y = v[1];
  double& z = v[2];
  double& w = v[3];
};

constexpr Point::Point() : Point(0.0, 0.0, 0.0) {}

constexpr Point::Point(double ix, double iy, double iz) : v{ix, iy, iz, 1.0} {}
