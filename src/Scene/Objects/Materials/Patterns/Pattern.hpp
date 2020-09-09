#pragma once

#include "Core/Color.hpp"
#include "Core/Point.hpp"

class Pattern {
 public:
  virtual const Color& color_at(const Point& point) const = 0;
};
