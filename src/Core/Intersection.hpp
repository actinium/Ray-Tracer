#pragma once

#include <vector>

class Intersection {
 public:
  constexpr Intersection(double t) noexcept;

 public:
  double t;
};

constexpr Intersection::Intersection(double it) noexcept : t{it} {}

using Intersections = std::vector<Intersection>;
