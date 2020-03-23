#pragma once

#include <initializer_list>

class Matrix {
 public:
  constexpr Matrix();
  constexpr Matrix(std::initializer_list<std::initializer_list<double>> im);

 public:
  alignas(32) double mat4[4][4];
};
