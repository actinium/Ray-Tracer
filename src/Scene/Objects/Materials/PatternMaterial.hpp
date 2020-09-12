#pragma once

#include "Scene/Objects/Materials/Material.hpp"
#include "Scene/Objects/Materials/Patterns/Pattern.hpp"

class PatternMaterial : public Material {
 public:
  constexpr PatternMaterial() noexcept;
  constexpr PatternMaterial(const Pattern* pattern) noexcept;
  constexpr PatternMaterial(const Pattern* pattern, double ambient,
                            double diffuse, double specular, double shininess,
                            double reflective) noexcept;

 public:
  Color color_at_object(const Object* object,
                        const Point& point) const override;

 public:
  const Pattern* pattern;
};

constexpr PatternMaterial::PatternMaterial() noexcept
    : Material(), pattern(nullptr) {}

constexpr PatternMaterial::PatternMaterial(const Pattern* p) noexcept
    : Material(), pattern(p) {}

constexpr PatternMaterial::PatternMaterial(const Pattern* p, double amb,
                                           double dif, double spec, double shin,
                                           double refl) noexcept
    : Material(amb, dif, spec, shin, refl), pattern(p) {}
