#pragma once

#include <vector>

#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"

class Light;
class Object;

class Scene {
 public:
  Scene() noexcept;
  Scene(const std::vector<const Light*>& lights,
        const std::vector<const Object*>& objects) noexcept;

 public:
  Intersections intersect(const Ray& ray) const;

 public:
  std::vector<const Light*> lights;
  std::vector<const Object*> objects;
};

inline Scene::Scene() noexcept : lights{}, objects{} {}

inline Scene::Scene(const std::vector<const Light*>& l,
                    const std::vector<const Object*>& o) noexcept
    : lights{l}, objects{o} {}
