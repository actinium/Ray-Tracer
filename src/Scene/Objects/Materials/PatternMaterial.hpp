#pragma once

#include "Scene/Objects/Materials/Material.hpp"
#include "Scene/Objects/Materials/Patterns/Pattern.hpp"

class PatternMaterial : public Material {
 public:
  constexpr PatternMaterial() noexcept;
  constexpr PatternMaterial(const Pattern* pattern, double ambient,
                            double diffuse, double specular,
                            double shininess) noexcept;

 public:
  const Color& color_at(const Point& point) const override;

 public:
  const Pattern* pattern;
};

constexpr PatternMaterial::PatternMaterial() noexcept
    : Material(), pattern(nullptr) {}

constexpr PatternMaterial::PatternMaterial(const Pattern* p, double amb,
                                           double dif, double spec,
                                           double shin) noexcept
    : Material(amb, dif, spec, shin), pattern(p) {}
