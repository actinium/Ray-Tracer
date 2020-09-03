#include "Transformations.hpp"

#include <cmath>

#include "Core/Math.hpp"

using std::cos;
using std::sin;

//------------------------------------------------------------------------------
// Translation
//------------------------------------------------------------------------------
Matrix translation(double x, double y, double z) {
  return Matrix(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}

//------------------------------------------------------------------------------
// Scaling
//------------------------------------------------------------------------------
Matrix scaling(double x, double y, double z) {
  return Matrix(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
}

Matrix scaling(double xyz) { return scaling(xyz, xyz, xyz); }

//------------------------------------------------------------------------------
// Rotation
//------------------------------------------------------------------------------
Matrix rotation_x(double r) {
  return Matrix(1, 0, 0, 0, 0, cos(r), -sin(r), 0, 0, sin(r), cos(r), 0, 0, 0,
                0, 1);
}

Matrix rotation_y(double r) {
  return Matrix(cos(r), 0, sin(r), 0, 0, 1, 0, 0, -sin(r), 0, cos(r), 0, 0, 0,
                0, 1);
}

Matrix rotation_z(double r) {
  return Matrix(cos(r), -sin(r), 0, 0, sin(r), cos(r), 0, 0, 0, 0, 1, 0, 0, 0,
                0, 1);
}

//------------------------------------------------------------------------------
// Shearing
//------------------------------------------------------------------------------
Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x,
                double z_y) {
  return Matrix(1, x_y, x_z, 0, y_x, 1, y_z, 0, z_x, z_y, 1, 0, 0, 0, 0, 1);
}

//------------------------------------------------------------------------------
// View Transformation
//------------------------------------------------------------------------------
Matrix view_transform(const Point &from, const Point &to, const Vector &up) {
  Vector forward = normalize(to - from);
  Vector left = cross(forward, normalize(up));
  Vector true_up = cross(left, forward);

  Matrix orientation(left.x, left.y, left.z, 0, true_up.x, true_up.y, true_up.z,
                     0, -forward.x, -forward.y, -forward.z, 0, 0, 0, 0, 1);

  return orientation * translation(-from.x, -from.y, -from.z);
}
