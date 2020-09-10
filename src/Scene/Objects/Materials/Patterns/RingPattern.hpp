#pragma once

#include "Scene/Objects/Materials/Patterns/TwoColorPattern.hpp"

class RingPattern : public TwoColorPattern {
 public:
  using TwoColorPattern::TwoColorPattern;

 public:
  Color color_at(const Point& point) const override;
};
