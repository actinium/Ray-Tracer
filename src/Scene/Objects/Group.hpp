#pragma once

#include <vector>

#include "Scene/Objects/Object.hpp"

class Group : public Object {
 public:
  Group() noexcept;

 private:
  Intersections local_intersect(const Ray& ray) const override;
  Vector local_normal_at(const Point& point) const override;

 public:
  const std::vector<const Object*>& objects() const { return objects_; };

 private:
  std::vector<const Object*> objects_;
};

inline Group::Group() noexcept : Object(), objects_{} {}
