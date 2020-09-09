#pragma once

#include <cmath>

#include "Scene/Objects/Materials/Patterns/TwoColorPattern.hpp"

using std::floor;

class StripePattern : public TwoColorPattern {
 public:
  using TwoColorPattern::TwoColorPattern;

 public:
  const Color& color_at(const Point& point) const override;
};
