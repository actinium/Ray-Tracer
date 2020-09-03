#include "Scene/Objects/Plane.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The normal of a plane is constant everywhere", "[Plane]") {
  Plane p;
  REQUIRE_THAT(p.normal_at(Point(0, 0, 0)), Equals(Vector(0, 1, 0)));
  REQUIRE_THAT(p.normal_at(Point(10, 0, -10)), Equals(Vector(0, 1, 0)));
  REQUIRE_THAT(p.normal_at(Point(-5, 0, 150)), Equals(Vector(0, 1, 0)));
}

TEST_CASE("Intersect with a ray parallel to the plane", "[Plane]") {
  Plane p;
  Ray r(Point(0, 10, 0), Vector(0, 0, 1));
  Intersections xs = p.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("Intersect with a coplanar ray", "[Plane]") {
  Plane p;
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Intersections xs = p.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray intersecting a plane from above", "[Plane]") {
  Plane p;
  Ray r(Point(0, 1, 0), Vector(0, -1, 0));
  Intersections xs = p.intersect(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == 1);
  REQUIRE(xs[0].object == &p);
}

TEST_CASE("A ray intersecting a plane from below", "[Plane]") {
  Plane p;
  Ray r(Point(0, -1, 0), Vector(0, 1, 0));
  Intersections xs = p.intersect(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == 1);
  REQUIRE(xs[0].object == &p);
}
