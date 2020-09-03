#include "Core/Matrix.hpp"
#include "Core/Point.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Core/Vector.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("Creating and querying a ray", "[Ray]") {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  REQUIRE_THAT(r.origin, Equals(Point(1, 2, 3)));
  REQUIRE_THAT(r.direction, Equals(Vector(4, 5, 6)));
}

TEST_CASE("Computing a point from a distance", "[Ray]") {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  REQUIRE_THAT(r.position(0), Equals(Point(2, 3, 4)));
  REQUIRE_THAT(r.position(1), Equals(Point(3, 3, 4)));
  REQUIRE_THAT(r.position(-1), Equals(Point(1, 3, 4)));
  REQUIRE_THAT(r.position(2.5), Equals(Point(4.5, 3, 4)));
}

//------------------------------------------------------------------------------
// Transformation
//------------------------------------------------------------------------------
TEST_CASE("Translating a ray", "[Ray]") {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m = translation(3, 4, 5);
  Ray r2 = r.transform(m);
  REQUIRE_THAT(r2.origin, Equals(Point(4, 6, 8)));
  REQUIRE_THAT(r2.direction, Equals(Vector(0, 1, 0)));
}

TEST_CASE("Scaling a ray", "[Ray]") {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m = scaling(2, 3, 4);
  Ray r2 = r.transform(m);
  REQUIRE_THAT(r2.origin, Equals(Point(2, 6, 12)));
  REQUIRE_THAT(r2.direction, Equals(Vector(0, 3, 0)));
}
