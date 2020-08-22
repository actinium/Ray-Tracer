#pragma once

#include "Matrix.hpp"
#include "Point.hpp"
#include "Vector.hpp"

class Ray {
 public:
  constexpr Ray(Point origin, Vector direction) noexcept;

 public:
  const Point origin;
  const Vector direction;
};

constexpr Ray::Ray(Point o, Vector d) noexcept : origin{o}, direction{d} {}

Point position(const Ray& ray, double t);

Ray transform(const Ray& ray, const Matrix& matrix);
