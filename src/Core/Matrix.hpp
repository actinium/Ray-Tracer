#pragma once

#include <initializer_list>

class Matrix {
 public:
  constexpr Matrix() noexcept;
  constexpr Matrix(
      std::initializer_list<std::initializer_list<double>> im) noexcept;

 public:
  alignas(32) double mat4[4][4];
};
