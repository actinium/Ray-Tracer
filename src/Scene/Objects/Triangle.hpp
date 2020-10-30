#pragma once

#include "Core/Point.hpp"
#include "Scene/Objects/Object.hpp"

class Triangle : public Object {
 public:
  Triangle(const Point& p1, const Point& p2, const Point& p3) noexcept;

 private:
  Intersections local_intersect(const Ray& ray) const override;
  Vector local_normal_at(const Point& point) const override;

 public:
  Point p1;
  Point p2;
  Point p3;

  Vector e1;
  Vector e2;

  Vector normal;
};

inline Triangle::Triangle(const Point& p1_, const Point& p2_,
                          const Point& p3_) noexcept
    : Object(),
      p1(p1_),
      p2(p2_),
      p3(p3_),
      e1(p2 - p1),
      e2(p3 - p1),
      normal(normalize(cross(e2, e1))) {}
