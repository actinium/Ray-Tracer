#pragma once

#include <vector>

class Object;

class Intersection {
 public:
  constexpr Intersection(double t, Object* object) noexcept;

 public:
  const double t;
  Object const* const object;
};

constexpr Intersection::Intersection(double it, Object* obj) noexcept
    : t{it}, object{obj} {}

using Intersections = std::vector<Intersection>;
