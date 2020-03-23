#pragma once

class Vector {
 public:
  constexpr Vector();
  constexpr Vector(double ix, double iy, double iz);

 public:
  alignas(32) double vec4[4];

 public:
  double& x = vec4[0];
  double& y = vec4[1];
  double& z = vec4[2];
  double& w = vec4[3];
};

constexpr Vector::Vector() : Vector(0.0, 0.0, 0.0) {}

constexpr Vector::Vector(double ix, double iy, double iz)
    : vec4{ix, iy, iz, 0.0} {}
