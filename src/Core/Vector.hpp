#pragma once

class Vector {
 public:
  constexpr Vector();
  constexpr Vector(double ix, double iy, double iz);

 public:
  alignas(32) double v[4];

 public:
  double& x = v[0];
  double& y = v[1];
  double& z = v[2];
  double& w = v[3];
};

constexpr Vector::Vector() : Vector(0.0, 0.0, 0.0) {}

constexpr Vector::Vector(double ix, double iy, double iz)
    : v{ix, iy, iz, 0.0} {}
