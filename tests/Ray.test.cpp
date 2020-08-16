#include "Core/Point.hpp"
#include "Core/Ray.hpp"
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
  REQUIRE_THAT(position(r, 0), Equals(Point(2, 3, 4)));
  REQUIRE_THAT(position(r, 1), Equals(Point(3, 3, 4)));
  REQUIRE_THAT(position(r, -1), Equals(Point(1, 3, 4)));
  REQUIRE_THAT(position(r, 2.5), Equals(Point(4.5, 3, 4)));
}
