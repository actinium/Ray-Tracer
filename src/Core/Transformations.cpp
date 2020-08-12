#include "Transformations.hpp"

#include <cmath>

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
                double z_y);

//------------------------------------------------------------------------------
// View Transformation
//------------------------------------------------------------------------------
Matrix view_transform(const Point &from, const Point &to, const Vector &up);
