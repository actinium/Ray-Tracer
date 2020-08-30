#pragma once

#include <optional>
#include <vector>

class Object;

class Intersection {
 public:
  constexpr Intersection(double t, Object const* const object) noexcept;

 public:
  double t;
  Object const* object;
};

constexpr Intersection::Intersection(double it,
                                     Object const* const obj) noexcept
    : t{it}, object{obj} {}

constexpr bool operator<(const Intersection& i1, const Intersection& i2) {
  return i1.t < i2.t;
}

using Intersections = std::vector<Intersection>;

using Hit = std::optional<Intersection>;

Hit hit(Intersections is);
