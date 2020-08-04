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
Point operator-(const Point& p) {
  Point r;
  vec4_neg(p.vec4, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------------
namespace {
void vec4_scalar_mul(double s, const double (&a)[4], double (&r)[4]) {
  r[0] = s * a[0];
  r[1] = s * a[1];
  r[2] = s * a[2];
  r[3] = s * a[3];
}

void vec4_cross(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[1] * b[2] - a[2] * b[1];
  r[1] = a[2] * b[0] - a[0] * b[2];
  r[2] = a[0] * b[1] - a[1] * b[0];
}

void vec4_dot(const double (&a)[4], const double (&b)[4], double& r) {
  r = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}
}  // namespace

// Matrix operator*(const Matrix& m1, const Matrix& m2);
// Vector operator*(const Matrix& m, const Vector& v);
// Point operator*(const Matrix& m, const Point& p);

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

//------------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------------
namespace {
void vec4_scalar_div(double s, const double (&a)[4], double (&r)[4]) {
  r[0] = s / a[0];
  r[1] = s / a[1];
  r[2] = s / a[2];
  r[3] = s / a[3];
}

void vec4_scalar_div(const double (&a)[4], double s, double (&r)[4]) {
  r[0] = a[0] / s;
  r[1] = a[1] / s;
  r[2] = a[2] / s;
  r[3] = a[3] / s;
}
}  // namespace

Vector operator/(double s, const Vector& v) {
  Vector r;
  vec4_scalar_div(s, v.vec4, r.vec4);
  return r;
}

Vector operator/(const Vector& v, double s) {
  Vector r;
  vec4_scalar_div(v.vec4, s, r.vec4);
  return r;
}

//------------------------------------------------------------------------------
// Magnitude
//------------------------------------------------------------------------------
namespace {}
double magnitude(const Vector& v);
Vector normalize(const Vector& v);
