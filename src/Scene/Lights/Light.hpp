#pragma once

#include "Core/Color.hpp"
#include "Core/Point.hpp"

class Light {
 public:
  constexpr Light(Point position, Color intensity) noexcept;

 public:
  Point position;
  Color intensity;
};

constexpr Light::Light(Point p, Color i) noexcept : position{p}, intensity{i} {}
