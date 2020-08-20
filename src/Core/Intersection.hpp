#pragma once

#include <optional>
#include <vector>

class Object;

class Intersection {
 public:
  constexpr Intersection(double t, Object const* const object) noexcept;

 public:
  const double t;
  Object const* const object;
};

constexpr Intersection::Intersection(double it,
                                     Object const* const obj) noexcept
    : t{it}, object{obj} {}

using Intersections = std::vector<Intersection>;

using Hit = std::optional<Intersection>;

Hit hit(Intersections is);
