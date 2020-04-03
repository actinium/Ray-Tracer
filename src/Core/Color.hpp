#pragma once

class Color {
 public:
  constexpr Color() noexcept;
  constexpr Color(double ix, double iy, double iz) noexcept;
  constexpr Color& operator=(const Color& other) noexcept;

 public:
  alignas(32) double vec4[4];

 public:
  double& red = vec4[0];
  double& green = vec4[1];
  double& blue = vec4[2];
};

constexpr Color::Color() noexcept : Color(0.0, 0.0, 0.0) {}

constexpr Color::Color(double r, double g, double b) noexcept
    : vec4{r, g, b, 0.0} {}

constexpr Color& Color::operator=(const Color& other) noexcept {
  vec4[0] = other.vec4[0];
  vec4[1] = other.vec4[1];
  vec4[2] = other.vec4[2];
  vec4[3] = other.vec4[3];
  return *this;
}
