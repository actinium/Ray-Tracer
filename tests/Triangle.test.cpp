#include "Core/Point.hpp"
#include "Scene/Objects/Triangle.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("Constructing a triangle", "[Triangle]") {
  Point p1(0, 1, 0);
  Point p2(-1, 0, 0);
  Point p3(1, 0, 0);
  Triangle t(p1, p2, p3);

  REQUIRE_THAT(t.p1, Equals(p1));
  REQUIRE_THAT(t.p2, Equals(p2));
  REQUIRE_THAT(t.p3, Equals(p3));
  REQUIRE_THAT(t.e1, Equals(Vector(-1, -1, 0)));
  REQUIRE_THAT(t.e2, Equals(Vector(1, -1, 0)));
  REQUIRE_THAT(t.normal, Equals(Vector(0, 0, -1)));
}

//------------------------------------------------------------------------------
// Normal Vector
//------------------------------------------------------------------------------
TEST_CASE("Finding the normal on a triangle", "[Triangle]") {
  Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

  Vector n1 = t.normal_at(Point(0, 0.5, 0));
  Vector n2 = t.normal_at(Point(-0.5, 0.75, 0));
  Vector n3 = t.normal_at(Point(0.5, 0.25, 0));

  REQUIRE_THAT(n1, Equals(t.normal));
  REQUIRE_THAT(n2, Equals(t.normal));
  REQUIRE_THAT(n3, Equals(t.normal));
}

//------------------------------------------------------------------------------
// Intersection
//------------------------------------------------------------------------------
TEST_CASE("Intersecting a ray parallel to the triangle", "[Triangle]") {
  Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r(Point(0, -1, -2), Vector(0, 1, 0));
  Intersections xs = t.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the p1-p3 edge", "[Triangle]") {
  Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r(Point(1, 1, -2), Vector(0, 0, 1));
  Intersections xs = t.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the p1-p2 edge", "[Triangle]") {
  Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r(Point(-1, 1, -2), Vector(0, 0, 1));
  Intersections xs = t.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the p2-p3 edge", "[Triangle]") {
  Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r(Point(0, -1, -2), Vector(0, 0, 1));
  Intersections xs = t.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray strikes a triangle", "[Triangle]") {
  Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  Ray r(Point(0, 0.5, -2), Vector(0, 0, 1));
  Intersections xs = t.intersect(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == 2);
}
