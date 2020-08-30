#include "PreparedComputations.hpp"

#include "Math.hpp"
#include "Scene/Objects/Object.hpp"

PreparedComputations prepare_computations(const Intersection& i, const Ray& r) {
  PreparedComputations comps;

  comps.t = i.t;
  comps.object = i.object;

  comps.point = position(r, i.t);
  comps.eye_vector = -r.direction;
  comps.normal_vector = comps.object->normal_at(comps.point);
  if (dot(comps.normal_vector, comps.eye_vector) < 0) {
    comps.inside = true;
    comps.normal_vector = -comps.normal_vector;
  } else {
    comps.inside = false;
  }

  return comps;
}
