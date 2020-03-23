#include "Math.hpp"

namespace {
void vec4_add(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[0] + b[0];
  r[1] = a[1] + b[1];
  r[2] = a[2] + b[2];
  r[3] = a[3] + b[3];
}

void vec4_sub(const double (&a)[4], const double (&b)[4], double (&r)[4]) {
  r[0] = a[0] + b[0];
  r[1] = a[1] + b[1];
  r[2] = a[2] + b[2];
  r[3] = a[3] + b[3];
}

}  // namespace

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
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
