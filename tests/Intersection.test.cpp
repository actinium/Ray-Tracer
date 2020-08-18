#include "Core/Intersection.hpp"
#include "Core/Point.hpp"
#include "Core/Ray.hpp"
#include "Core/Vector.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("An intersection encapsulates t and object", "[Intersection]") {
  Sphere s;
  Intersection i(3.5, &s);
  REQUIRE(i.t == Approx(3.5));
  REQUIRE(i.object == &s);
}

TEST_CASE("Aggregating intersections", "[Intersection]") {
  Sphere s;
  Intersections xs;
  xs.emplace_back(1, &s);
  xs.emplace_back(2, &s);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(1));
  REQUIRE(xs[1].t == Approx(2));
}

TEST_CASE("Intersect sets the object on the intersection", "[Intersection]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].object == &s);
  REQUIRE(xs[1].object == &s);
}
