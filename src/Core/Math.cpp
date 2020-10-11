#include "Math.hpp"

#include <cmath>

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
namespace {
void vec4_add(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[0] + b[0];
  r[1] = a[1] + b[1];
  r[2] = a[2] + b[2];
  r[3] = a[3] + b[3];
}
}  // namespace

Vector operator+(const Vector& v1, const Vector& v2) {
  Vector r;
  vec4_add(v1.vec4, v2.vec4, r.vec4);
  return r;
}

Point operator+(const Point& p, const Vector& v) {
  Point r;
  vec4_add(p.vec4, v.vec4, r.vec4);
  return r;
}

Color operator+(const Color& c1, const Color& c2) {
  Color r;
  vec4_add(c1.vec4, c2.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
namespace {
void vec4_sub(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[0] - b[0];
  r[1] = a[1] - b[1];
  r[2] = a[2] - b[2];
  r[3] = a[3] - b[3];
}
}  // namespace

Vector operator-(const Vector& v1, const Vector& v2) {
  Vector r;
  vec4_sub(v1.vec4, v2.vec4, r.vec4);
  return r;
}

Vector operator-(const Point& p1, const Point& p2) {
  Vector r;
  vec4_sub(p1.vec4, p2.vec4, r.vec4);
  return r;
}

Point operator-(const Point& p, const Vector& v) {
  Point r;
  vec4_sub(p.vec4, v.vec4, r.vec4);
  return r;
}

Color operator-(const Color& c1, const Color& c2) {
  Color r;
  vec4_sub(c1.vec4, c2.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Negation
//------------------------------------------------------------------------------
namespace {
void vec4_neg(const double (&a)[4], double (&r)[4]) {
  r[0] = -a[0];
  r[1] = -a[1];
  r[2] = -a[2];
  r[3] = -a[3];
}
}  // namespace

Vector operator-(const Vector& v) {
  Vector r;
  vec4_neg(v.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------------
namespace {
void mat4_mul(const double (&a)[4][4], const double (&b)[4][4],
              double (&r)[4][4]) {
  for (std::size_t row = 0; row < 4; ++row) {
    for (std::size_t col = 0; col < 4; ++col) {
      r[row][col] = a[row][0] * b[0][col] + a[row][1] * b[1][col] +
                    a[row][2] * b[2][col] + a[row][3] * b[3][col];
    }
  }
}

void mat4_vec4_mul(const double (&a)[4][4], const double (&b)[4],
                   double (&r)[4]) {
  for (std::size_t row = 0; row < 4; ++row) {
    r[row] = a[row][0] * b[0] + a[row][1] * b[1] + a[row][2] * b[2] +
             a[row][3] * b[3];
  }
}

void vec4_cross(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[1] * b[2] - a[2] * b[1];
  r[1] = a[2] * b[0] - a[0] * b[2];
  r[2] = a[0] * b[1] - a[1] * b[0];
}

void vec4_dot(const double (&a)[4], const double (&b)[4], double& r) {
  r = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

void vec4_hadamard(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[0] * b[0];
  r[1] = a[1] * b[1];
  r[2] = a[2] * b[2];
  r[3] = a[3] * b[3];
}
}  // namespace

Matrix operator*(const Matrix& m1, const Matrix& m2) {
  Matrix r;
  mat4_mul(m1.mat4, m2.mat4, r.mat4);
  return r;
}

Vector operator*(const Matrix& m, const Vector& v) {
  Vector r;
  mat4_vec4_mul(m.mat4, v.vec4, r.vec4);
  return r;
}

Point operator*(const Matrix& m, const Point& p) {
  Point r;
  mat4_vec4_mul(m.mat4, p.vec4, r.vec4);
  return r;
}

Vector cross(const Vector& v1, const Vector& v2) {
  Vector r;
  vec4_cross(v1.vec4, v2.vec4, r.vec4);
  return r;
}

double dot(const Vector& v1, const Vector& v2) {
  double r;
  vec4_dot(v1.vec4, v2.vec4, r);
  return r;
}

Color operator*(const Color& c1, const Color& c2) {
  Color r;
  vec4_hadamard(c1.vec4, c2.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Scalar Multiplication
//------------------------------------------------------------------------------
namespace {
void vec4_scalar_mul(double s, const double (&a)[4], double (&r)[4]) {
  r[0] = s * a[0];
  r[1] = s * a[1];
  r[2] = s * a[2];
  r[3] = s * a[3];
}
}  // namespace

Vector operator*(double s, const Vector& v) {
  Vector r;
  vec4_scalar_mul(s, v.vec4, r.vec4);
  return r;
}

Vector operator*(const Vector& v, double s) {
  Vector r;
  vec4_scalar_mul(s, v.vec4, r.vec4);
  return r;
}

Color operator*(double s, const Color& c) {
  Color r;
  vec4_scalar_mul(s, c.vec4, r.vec4);
  return r;
}

Color operator*(const Color& c, double s) {
  Color r;
  vec4_scalar_mul(s, c.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------------
namespace {

void vec4_scalar_div(const double (&a)[4], double s, double (&r)[4]) {
  r[0] = a[0] / s;
  r[1] = a[1] / s;
  r[2] = a[2] / s;
  r[3] = a[3] / s;
}
}  // namespace

Vector operator/(const Vector& v, double s) {
  Vector r;
  vec4_scalar_div(v.vec4, s, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Magnitude
//------------------------------------------------------------------------------
namespace {
void vec4_mag(const double (&v)[4], double& r) {
  r = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}

void vec4_norm(const double (&v)[4], double (&r)[4]) {
  double mag;
  vec4_mag(v, mag);
  if (mag == 0) return;
  r[0] = v[0] / mag;
  r[1] = v[1] / mag;
  r[2] = v[2] / mag;
  r[3] = v[3] / mag;
}
}  // namespace

double magnitude(const Vector& v) {
  double r;
  vec4_mag(v.vec4, r);
  return r;
}

Vector normalize(const Vector& v) {
  Vector r;
  vec4_norm(v.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Reflection
//------------------------------------------------------------------------------
namespace {
void vec4_reflect(const double (&v)[4], const double (&n)[4], double (&r)[4]) {
  // r = v - n * 2 * dot(v, n)
  double d;
  vec4_dot(v, n, d);
  vec4_scalar_mul(2 * d, n, r);
  vec4_sub(v, r, r);
}
}  // namespace

Vector reflect(const Vector& v, const Vector& n) {
  Vector r;
  vec4_reflect(v.vec4, n.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Transposition
//------------------------------------------------------------------------------
namespace {
void mat4_transpose(const double (&a)[4][4], double (&r)[4][4]) {
  for (std::size_t row = 0; row < 4; ++row) {
    for (std::size_t col = 0; col < 4; ++col) {
      r[row][col] = a[col][row];
    }
  }
}
}  // namespace

Matrix transpose(const Matrix& m) {
  Matrix r;
  mat4_transpose(m.mat4, r.mat4);
  return r;
}

//------------------------------------------------------------------------------
// Inversion
//------------------------------------------------------------------------------
namespace {
void mat4_inverse(const double (&a)[4][4], double (&r)[4][4]) {
  double det = a[0][3] * a[1][2] * a[2][1] * a[3][0] -
               a[0][2] * a[1][3] * a[2][1] * a[3][0] -
               a[0][3] * a[1][1] * a[2][2] * a[3][0] +
               a[0][1] * a[1][3] * a[2][2] * a[3][0] +
               a[0][2] * a[1][1] * a[2][3] * a[3][0] -
               a[0][1] * a[1][2] * a[2][3] * a[3][0] -
               a[0][3] * a[1][2] * a[2][0] * a[3][1] +
               a[0][2] * a[1][3] * a[2][0] * a[3][1] +
               a[0][3] * a[1][0] * a[2][2] * a[3][1] -
               a[0][0] * a[1][3] * a[2][2] * a[3][1] -
               a[0][2] * a[1][0] * a[2][3] * a[3][1] +
               a[0][0] * a[1][2] * a[2][3] * a[3][1] +
               a[0][3] * a[1][1] * a[2][0] * a[3][2] -
               a[0][1] * a[1][3] * a[2][0] * a[3][2] -
               a[0][3] * a[1][0] * a[2][1] * a[3][2] +
               a[0][0] * a[1][3] * a[2][1] * a[3][2] +
               a[0][1] * a[1][0] * a[2][3] * a[3][2] -
               a[0][0] * a[1][1] * a[2][3] * a[3][2] -
               a[0][2] * a[1][1] * a[2][0] * a[3][3] +
               a[0][1] * a[1][2] * a[2][0] * a[3][3] +
               a[0][2] * a[1][0] * a[2][1] * a[3][3] -
               a[0][0] * a[1][2] * a[2][1] * a[3][3] -
               a[0][1] * a[1][0] * a[2][2] * a[3][3] +
               a[0][0] * a[1][1] * a[2][2] * a[3][3];

  r[0][0] = (a[1][2] * a[2][3] * a[3][1] - a[1][3] * a[2][2] * a[3][1] +
             a[1][3] * a[2][1] * a[3][2] - a[1][1] * a[2][3] * a[3][2] -
             a[1][2] * a[2][1] * a[3][3] + a[1][1] * a[2][2] * a[3][3]) /
            det;
  r[0][1] = (a[0][3] * a[2][2] * a[3][1] - a[0][2] * a[2][3] * a[3][1] -
             a[0][3] * a[2][1] * a[3][2] + a[0][1] * a[2][3] * a[3][2] +
             a[0][2] * a[2][1] * a[3][3] - a[0][1] * a[2][2] * a[3][3]) /
            det;
  r[0][2] = (a[0][2] * a[1][3] * a[3][1] - a[0][3] * a[1][2] * a[3][1] +
             a[0][3] * a[1][1] * a[3][2] - a[0][1] * a[1][3] * a[3][2] -
             a[0][2] * a[1][1] * a[3][3] + a[0][1] * a[1][2] * a[3][3]) /
            det;
  r[0][3] = (a[0][3] * a[1][2] * a[2][1] - a[0][2] * a[1][3] * a[2][1] -
             a[0][3] * a[1][1] * a[2][2] + a[0][1] * a[1][3] * a[2][2] +
             a[0][2] * a[1][1] * a[2][3] - a[0][1] * a[1][2] * a[2][3]) /
            det;
  r[1][0] = (a[1][3] * a[2][2] * a[3][0] - a[1][2] * a[2][3] * a[3][0] -
             a[1][3] * a[2][0] * a[3][2] + a[1][0] * a[2][3] * a[3][2] +
             a[1][2] * a[2][0] * a[3][3] - a[1][0] * a[2][2] * a[3][3]) /
            det;
  r[1][1] = (a[0][2] * a[2][3] * a[3][0] - a[0][3] * a[2][2] * a[3][0] +
             a[0][3] * a[2][0] * a[3][2] - a[0][0] * a[2][3] * a[3][2] -
             a[0][2] * a[2][0] * a[3][3] + a[0][0] * a[2][2] * a[3][3]) /
            det;
  r[1][2] = (a[0][3] * a[1][2] * a[3][0] - a[0][2] * a[1][3] * a[3][0] -
             a[0][3] * a[1][0] * a[3][2] + a[0][0] * a[1][3] * a[3][2] +
             a[0][2] * a[1][0] * a[3][3] - a[0][0] * a[1][2] * a[3][3]) /
            det;
  r[1][3] = (a[0][2] * a[1][3] * a[2][0] - a[0][3] * a[1][2] * a[2][0] +
             a[0][3] * a[1][0] * a[2][2] - a[0][0] * a[1][3] * a[2][2] -
             a[0][2] * a[1][0] * a[2][3] + a[0][0] * a[1][2] * a[2][3]) /
            det;
  r[2][0] = (a[1][1] * a[2][3] * a[3][0] - a[1][3] * a[2][1] * a[3][0] +
             a[1][3] * a[2][0] * a[3][1] - a[1][0] * a[2][3] * a[3][1] -
             a[1][1] * a[2][0] * a[3][3] + a[1][0] * a[2][1] * a[3][3]) /
            det;
  r[2][1] = (a[0][3] * a[2][1] * a[3][0] - a[0][1] * a[2][3] * a[3][0] -
             a[0][3] * a[2][0] * a[3][1] + a[0][0] * a[2][3] * a[3][1] +
             a[0][1] * a[2][0] * a[3][3] - a[0][0] * a[2][1] * a[3][3]) /
            det;
  r[2][2] = (a[0][1] * a[1][3] * a[3][0] - a[0][3] * a[1][1] * a[3][0] +
             a[0][3] * a[1][0] * a[3][1] - a[0][0] * a[1][3] * a[3][1] -
             a[0][1] * a[1][0] * a[3][3] + a[0][0] * a[1][1] * a[3][3]) /
            det;
  r[2][3] = (a[0][3] * a[1][1] * a[2][0] - a[0][1] * a[1][3] * a[2][0] -
             a[0][3] * a[1][0] * a[2][1] + a[0][0] * a[1][3] * a[2][1] +
             a[0][1] * a[1][0] * a[2][3] - a[0][0] * a[1][1] * a[2][3]) /
            det;
  r[3][0] = (a[1][2] * a[2][1] * a[3][0] - a[1][1] * a[2][2] * a[3][0] -
             a[1][2] * a[2][0] * a[3][1] + a[1][0] * a[2][2] * a[3][1] +
             a[1][1] * a[2][0] * a[3][2] - a[1][0] * a[2][1] * a[3][2]) /
            det;
  r[3][1] = (a[0][1] * a[2][2] * a[3][0] - a[0][2] * a[2][1] * a[3][0] +
             a[0][2] * a[2][0] * a[3][1] - a[0][0] * a[2][2] * a[3][1] -
             a[0][1] * a[2][0] * a[3][2] + a[0][0] * a[2][1] * a[3][2]) /
            det;
  r[3][2] = (a[0][2] * a[1][1] * a[3][0] - a[0][1] * a[1][2] * a[3][0] -
             a[0][2] * a[1][0] * a[3][1] + a[0][0] * a[1][2] * a[3][1] +
             a[0][1] * a[1][0] * a[3][2] - a[0][0] * a[1][1] * a[3][2]) /
            det;
  r[3][3] = (a[0][1] * a[1][2] * a[2][0] - a[0][2] * a[1][1] * a[2][0] +
             a[0][2] * a[1][0] * a[2][1] - a[0][0] * a[1][2] * a[2][1] -
             a[0][1] * a[1][0] * a[2][2] + a[0][0] * a[1][1] * a[2][2]) /
            det;
}
}  // namespace

Matrix inverse(const Matrix& m) {
  Matrix r;
  mat4_inverse(m.mat4, r.mat4);
  return r;
}
