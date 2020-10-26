#include "Scene.hpp"

#include <algorithm>

#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Object.hpp"

Intersections Scene::intersect(const Ray& ray) const {
  Intersections is;
  for (const Object* o : objects) {
    o->intersect(ray, is);
  }
  std::sort(is.begin(), is.end());
  return is;
}
