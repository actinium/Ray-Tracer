#include <cmath>

#include "Core/Intersection.hpp"
#include "Core/Lighting.hpp"
#include "Core/Point.hpp"
#include "Core/Ray.hpp"
#include "Core/Vector.hpp"
#include "Scene/Objects/Plane.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

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
  Hit hit = get_first_hit(xs);
  REQUIRE(hit.has_value());
  REQUIRE_THAT(hit.value(), Equals(i1));
}

TEST_CASE("The hit, when some intersections have negative t",
          "[Intersection]") {
  Sphere s;
  Intersection i1(-1, &s);
  Intersection i2(1, &s);
  Intersections xs;
  xs.push_back(i2);
  xs.push_back(i1);
  Hit hit = get_first_hit(xs);
  REQUIRE(hit.has_value());
  REQUIRE_THAT(hit.value(), Equals(i2));
}

TEST_CASE("The hit, when all intersections have negative t", "[Intersection]") {
  Sphere s;
  Intersection i1(-2, &s);
  Intersection i2(-1, &s);
  Intersections xs;
  xs.push_back(i2);
  xs.push_back(i1);
  Hit hit = get_first_hit(xs);
  REQUIRE_FALSE(hit.has_value());
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
  Hit hit = get_first_hit(xs);
  REQUIRE(hit.has_value());
  REQUIRE_THAT(hit.value(), Equals(i4));
}

//------------------------------------------------------------------------------
// Prepared Computations
//------------------------------------------------------------------------------
TEST_CASE("Precomputing the state of an intersection", "[Intersection]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, &shape);
  PreparedComputations comps = prepare_computations(i, r);
  REQUIRE(comps.t == i.t);
  REQUIRE(comps.object == i.object);
  REQUIRE_THAT(comps.point, Equals(Point(0, 0, -1)));
  REQUIRE_THAT(comps.eye_vector, Equals(Vector(0, 0, -1)));
  REQUIRE_THAT(comps.normal_vector, Equals(Vector(0, 0, -1)));
}

TEST_CASE("The hit, when an intersection occurs on the outside",
          "[Intersection]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, &shape);
  PreparedComputations comps = prepare_computations(i, r);
  REQUIRE_FALSE(comps.inside);
}

TEST_CASE("The hit, when an intersection occurs on the inside",
          "[Intersection]") {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere shape;
  Intersection i(1, &shape);
  PreparedComputations comps = prepare_computations(i, r);
  REQUIRE_THAT(comps.point, Equals(Point(0, 0, 1)));
  REQUIRE_THAT(comps.eye_vector, Equals(Vector(0, 0, -1)));
  REQUIRE(comps.inside);
  REQUIRE_THAT(comps.normal_vector, Equals(Vector(0, 0, -1)));
}

TEST_CASE("The hit should offset the point", "[Intersection]") {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere shape;
  shape.set_transform(translation(0, 0, 1));
  Intersection i(5, &shape);
  PreparedComputations comps = prepare_computations(i, r);
  REQUIRE(comps.over_point.z < -EPSILON / 2);
  REQUIRE(comps.point.z > comps.over_point.z);
}

//------------------------------------------------------------------------------
// Reflection
//------------------------------------------------------------------------------
TEST_CASE("Precomputing the reflection vector", "[Intersection]") {
  Plane shape;
  Ray r(Point(0, 1, -1), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  Intersection i(sqrt(2), &shape);
  PreparedComputations comps = prepare_computations(i, r);
  REQUIRE_THAT(comps.reflect_vector,
               Equals(Vector(0, sqrt(2) / 2, sqrt(2) / 2)));
}
