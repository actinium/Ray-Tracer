#include <cmath>

#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Objects/Cone.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

using std::sqrt;

TEST_CASE("Intersecting a cone with a ray", "[Cone]") {
  // Examples:
  //  | origin          | direction           | t0      | t1       |
  //  | point(0, 0, -5) | vector(0, 0, 1)     | 5       |  5       |
  //  | point(0, 0, -5) | vector(1, 1, 1)     | 8.66025 |  8.66025 |
  //  | point(1, 1, -5) | vector(-0.5, -1, 1) | 4.55006 | 49.44994 |

  using example = std::tuple<Point, Vector, double, double>;
  auto examples = GENERATE(table<Point, Vector, double, double>(
      {example{Point(0, 0, -5), Vector(0, 0, 1), 5, 5},
       example{Point(0, 0, -5), Vector(1, 1, 1), 8.66025, 8.66025},
       example{Point(1, 1, -5), Vector(-0.5, -1, 1), 4.55006, 49.44994}}));

  Cone cone;
  Point origin = std::get<0>(examples);
  Vector direction = normalize(std::get<1>(examples));
  Ray r(origin, direction);
  Intersections xs = cone.intersect(r);

  double t0 = std::get<2>(examples);
  double t1 = std::get<3>(examples);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(t0));
  REQUIRE(xs[1].t == Approx(t1));
}

TEST_CASE("Intersecting a cone with a ray parallel to one of its halves",
          "[Cone]") {
  Cone cone;
  Vector direction = normalize(Vector(0, 1, 1));
  Ray r(Point(0, 0, -1), direction);
  Intersections xs = cone.intersect(r);
  REQUIRE(xs.size() == 1);
  REQUIRE(xs[0].t == Approx(0.35355));
}

TEST_CASE("Intersecting a cone's end caps", "[Cone]") {
  // Examples:
  //  | origin             | direction       | count |
  //  | point(0, 0, -5)    | vector(0, 1, 0) | 0     |
  //  | point(0, 0, -0.25) | vector(0, 1, 1) | 2     |
  //  | point(0, 0, -0.25) | vector(0, 1, 0) | 4     |

  using example = std::tuple<Point, Vector, double>;
  auto examples = GENERATE(table<Point, Vector, double>(
      {example{Point(0, 0, -5), Vector(0, 1, 0), 0},
       example{Point(0, 0, -0.25), Vector(0, 1, 1), 2},
       example{Point(0, 0, -0.25), Vector(0, 1, 0), 4}}));

  Cone cone;
  cone.minimum = -0.5;
  cone.maximum = 0.5;
  cone.is_closed = true;

  Point origin = std::get<0>(examples);
  Vector direction = normalize(std::get<1>(examples));
  Ray r(origin, direction);
  Intersections xs = cone.intersect(r);
  REQUIRE(xs.size() == std::get<2>(examples));
}

TEST_CASE("Computing the normal vector on a cone", "[Cone]") {
  // Examples:
  //  | point             | normal                 |
  //  | point(0, 0, 0)    | vector(0, 0, 0)        |
  //  | point(1, 1, 1)    | vector(1, -√2, 1)      |
  //  | point(-1, -1, 0)  | vector(-1, 1, 0)       |

  using example = std::tuple<Point, Vector>;
  auto examples = GENERATE(
      table<Point, Vector>({example{Point(0, 0, 0), Vector(0, 0, 0)},
                            example{Point(1, 1, 1), Vector(1, -sqrt(2), 1)},
                            example{Point(-1, -1, 0), Vector(-1, 1, 0)}}));

  Cone cone;
  Point point = std::get<0>(examples);
  Vector normal = normalize(std::get<1>(examples));
  Vector n = cone.normal_at(point);
  REQUIRE_THAT(n, Equals(normal));
}
