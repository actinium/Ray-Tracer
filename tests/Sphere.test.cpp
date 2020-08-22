#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
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

//------------------------------------------------------------------------------
// Transformation
//------------------------------------------------------------------------------
TEST_CASE("A sphere's default transformation", "[Sphere]") {
  Sphere s;
  REQUIRE_THAT(s.transform(), Equals(Matrix::Identity));
}

TEST_CASE("Changing a sphere's transformation", "[Sphere]") {
  Sphere s;
  Matrix t = translation(2, 3, 4);
  s.set_transform(t);
  REQUIRE_THAT(s.transform(), Equals(t));
}

TEST_CASE("Intersecting a scaled sphere with a ray", "[Sphere]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.set_transform(scaling(2, 2, 2));
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(3));
  REQUIRE(xs[1].t == Approx(7));
}

TEST_CASE("Intersecting a translated sphere with a ray", "[Sphere]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.set_transform(translation(5, 0, 0));
  Intersections xs = s.intersect(r);
  REQUIRE(xs.size() == 0);
}
