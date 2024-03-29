#pragma once

class Matrix {
 public:
  constexpr Matrix() noexcept;
  constexpr Matrix(double m00, double m01, double m02, double m03, double m10,
                   double m11, double m12, double m13, double m20, double m21,
                   double m22, double m23, double m30, double m31, double m32,
                   double m33) noexcept;
  constexpr Matrix(const double (&m)[4][4]) noexcept;

  constexpr Matrix(const Matrix& other) noexcept;
  constexpr Matrix& operator=(const Matrix& other) noexcept;

 public:
  alignas(32) double mat4[4][4];

 public:
  static const Matrix Identity;
};

constexpr Matrix::Matrix() noexcept
    : mat4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} {}

constexpr Matrix::Matrix(double m00, double m01, double m02, double m03,
                         double m10, double m11, double m12, double m13,
                         double m20, double m21, double m22, double m23,
                         double m30, double m31, double m32,
                         double m33) noexcept
    : mat4{{m00, m01, m02, m03},
           {m10, m11, m12, m13},
           {m20, m21, m22, m23},
           {m30, m31, m32, m33}} {}

constexpr Matrix::Matrix(const double (&m)[4][4]) noexcept
    : mat4{{m[0][0], m[0][1], m[0][2], m[0][3]},
           {m[1][0], m[1][1], m[1][2], m[1][3]},
           {m[2][0], m[2][1], m[2][2], m[2][3]},
           {m[3][0], m[3][1], m[3][2], m[3][3]}} {}

constexpr Matrix::Matrix(const Matrix& other) noexcept : Matrix(other.mat4) {}

constexpr Matrix& Matrix::operator=(const Matrix& other) noexcept {
  mat4[0][0] = other.mat4[0][0];
  mat4[0][1] = other.mat4[0][1];
  mat4[0][2] = other.mat4[0][2];
  mat4[0][3] = other.mat4[0][3];
  mat4[1][0] = other.mat4[1][0];
  mat4[1][1] = other.mat4[1][1];
  mat4[1][2] = other.mat4[1][2];
  mat4[1][3] = other.mat4[1][3];
  mat4[2][0] = other.mat4[2][0];
  mat4[2][1] = other.mat4[2][1];
  mat4[2][2] = other.mat4[2][2];
  mat4[2][3] = other.mat4[2][3];
  mat4[3][0] = other.mat4[3][0];
  mat4[3][1] = other.mat4[3][1];
  mat4[3][2] = other.mat4[3][2];
  mat4[3][3] = other.mat4[3][3];
  return *this;
}
