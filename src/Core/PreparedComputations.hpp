#pragma once

#include "Intersection.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

class Object;

struct PreparedComputations {
  double t;
  const Object* object;
  Point point;
  Point over_point;
  Vector eye_vector;
  Vector normal_vector;
  bool inside;
};

PreparedComputations prepare_computations(const Intersection& i, const Ray& r);
