#include "Group.hpp"

#include <algorithm>
#include <stdexcept>

Intersections Group::local_intersect(const Ray& ray) const {
  Intersections is;
  for (const Object* obj : objects_) {
    Intersections obj_is = obj->intersect(ray);
    for (Intersection i : obj_is) {
      is.push_back(i);
    }
  }
  std::sort(is.begin(), is.end());
  return is;
}

Vector Group::local_normal_at(const Point&) const {
  throw std::domain_error("Groups don't have normals.");
}

void Group::add_child(Object* obj) {
  objects_.push_back(obj);
  obj->set_parent(this);
}
