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

//------------------------------------------------------------------------------
// Hit
//------------------------------------------------------------------------------
TEST_CASE("The hit, when all intersections have positive t", "[Intersection]") {
  Sphere s;
  Intersection i1(1.0, &s);
  Intersection i2(2.0, &s);
  Intersections xs;
  xs.push_back(i2);
  xs.push_back(i1);
  Hit h = hit(xs);
  REQUIRE(h.has_value());
  REQUIRE_THAT(h.value(), Equals(i1));
}

TEST_CASE("The hit, when some intersections have negative t",
          "[Intersection]") {
  Sphere s;
  Intersection i1(-1, &s);
  Intersection i2(1, &s);
  Intersections xs;
  xs.push_back(i2);
  xs.push_back(i1);
  Hit h = hit(xs);
  REQUIRE(h.has_value());
  REQUIRE_THAT(h.value(), Equals(i2));
}

TEST_CASE("The hit, when all intersections have negative t", "[Intersection]") {
  Sphere s;
  Intersection i1(-2, &s);
  Intersection i2(-1, &s);
  Intersections xs;
  xs.push_back(i2);
  xs.push_back(i1);
  Hit h = hit(xs);
  REQUIRE_FALSE(h.has_value());
}

TEST_CASE("The hit is always the lowest nonnegative intersection",
          "[Intersection]") {
  Sphere s;
  Intersection i1(5, &s);
  Intersection i2(7, &s);
  Intersection i3(-3, &s);
  Intersection i4(2, &s);
  Intersections xs;
  xs.push_back(i1);
  xs.push_back(i2);
  xs.push_back(i3);
  xs.push_back(i4);
  Hit h = hit(xs);
  REQUIRE(h.has_value());
  REQUIRE_THAT(h.value(), Equals(i4));
}