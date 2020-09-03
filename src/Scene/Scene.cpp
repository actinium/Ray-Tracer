#include "Scene.hpp"

#include <algorithm>

#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Object.hpp"

Intersections Scene::intersect(const Ray& ray) const {
  Intersections is;
  for (const Object* o : objects) {
    Intersections ois = o->intersect(ray);
    for (const Intersection& i : ois) {
      is.push_back(i);
    }
  }
  std::sort(is.begin(), is.end());
  return is;
}
