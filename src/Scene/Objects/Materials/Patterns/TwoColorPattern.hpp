#pragma once

#include "Scene/Objects/Materials/Patterns/Pattern.hpp"

class TwoColorPattern : public Pattern {
 public:
  constexpr TwoColorPattern(const Color& a, const Color& b) noexcept;

 protected:
  Color color_a;
  Color color_b;
};

constexpr TwoColorPattern::TwoColorPattern(const Color& a,
                                           const Color& b) noexcept
    : color_a(a), color_b(b) {}
