#pragma once

#include "Core/Matrix.hpp"
#include "Core/Point.hpp"
#include "Core/Vector.hpp"

class Ray {
 public:
  constexpr Ray(Point origin, Vector direction) noexcept;

 public:
  Point position(double t) const;
  Ray transform(const Matrix& matrix) const;

 public:
  const Point origin;
  const Vector direction;
};

constexpr Ray::Ray(Point o, Vector d) noexcept : origin{o}, direction{d} {}
