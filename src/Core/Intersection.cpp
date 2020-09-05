#include "Intersection.hpp"

#include "Core/Constants.hpp"

Hit get_first_hit(Intersections is) {
  double t_min = INF;
  const Object *target = nullptr;

  for (const Intersection &i : is) {
    if (i.t > 0 && i.t < t_min) {
      t_min = i.t;
      target = i.object;
    }
  }

  if (target != nullptr) {
    return Intersection{t_min, target};
  }
  return std::nullopt;
}
