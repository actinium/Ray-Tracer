#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("A ray intersects a sphere at two points", "[Sphere]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(4.0));
  REQUIRE(xs[1].t == Approx(6.0));
}

TEST_CASE("A ray intersects a sphere at a tangent", "[Sphere]") {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(5.0));
  REQUIRE(xs[1].t == Approx(5.0));
}

TEST_CASE("A ray misses a sphere", "[Sphere]") {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere", "[Sphere]") {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(-1.0));
  REQUIRE(xs[1].t == Approx(1.0));
}

TEST_CASE("A sphere is behind a ray", "[Sphere]") {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(-6.0));
  REQUIRE(xs[1].t == Approx(-4.0));
}
