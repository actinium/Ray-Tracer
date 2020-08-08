#pragma once

#include <string>

class Color {
 public:
  constexpr Color() noexcept;
  constexpr Color(double ix, double iy, double iz) noexcept;
  Color(const std::string& hex) noexcept;
  constexpr Color& operator=(const Color& other) noexcept;

 public:
  alignas(32) double vec4[4];

 public:
  double& red = vec4[0];
  double& green = vec4[1];
  double& blue = vec4[2];

 public:
  static const Color Black;
  static const Color Darkgrey;
  static const Color Grey;
  static const Color Lightgrey;
  static const Color White;

  static const Color Red;
  static const Color Orange;
  static const Color Yellow;
  static const Color Green;
  static const Color Turquoise;
  static const Color Cyan;
  static const Color Blue;
  static const Color Purple;
};

constexpr Color::Color() noexcept : Color(0.0, 0.0, 0.0) {}

constexpr Color::Color(double r, double g, double b) noexcept
    : vec4{r, g, b, 0.0} {}

inline Color::Color(const std::string& hex) noexcept
    : Color((double)std::stoi(hex.substr(0, 2), nullptr, 16) / 255,
            (double)std::stoi(hex.substr(2, 2), nullptr, 16) / 255,
            (double)std::stoi(hex.substr(4, 2), nullptr, 16) / 255) {}

constexpr Color& Color::operator=(const Color& other) noexcept {
  vec4[0] = other.vec4[0];
  vec4[1] = other.vec4[1];
  vec4[2] = other.vec4[2];
  vec4[3] = other.vec4[3];
  return *this;
}
