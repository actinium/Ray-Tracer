#include "Object.hpp"

#include "Core/Math.hpp"

void Object::set_transform(const Matrix& matrix) {
  transform_ = matrix;
  inv_transform_ = inverse(matrix);
}

void Object::set_material(const Material& m) { material_ = &m; }
