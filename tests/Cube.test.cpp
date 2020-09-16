#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Objects/Cube.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("A ray intersects a cube", "[Sphere]") {
  // Examples:
  // |        | origin            | direction        | t1 | t2 |
  // | +x     | point(5, 0.5, 0)  | vector(-1, 0, 0) |  4 |  6 |
  // | -x     | point(-5, 0.5, 0) | vector(1, 0, 0)  |  4 |  6 |
  // | +y     | point(0.5, 5, 0)  | vector(0, -1, 0) |  4 |  6 |
  // | -y     | point(0.5, -5, 0) | vector(0, 1, 0)  |  4 |  6 |
  // | +z     | point(0.5, 0, 5)  | vector(0, 0, -1) |  4 |  6 |
  // | -z     | point(0.5, 0, -5) | vector(0, 0, 1)  |  4 |  6 |
  // | inside | point(0, 0.5, 0)  | vector(0, 0, 1)  | -1 |  1 |

  using example = std::tuple<Point, Vector, double, double>;
  auto examples = GENERATE(table<Point, Vector, double, double>(
      {example{Point(5, 0.5, 0), Vector(-1, 0, 0), 4, 6},
       example{Point(-5, 0.5, 0), Vector(1, 0, 0), 4, 6},
       example{Point(0.5, 5, 0), Vector(0, -1, 0), 4, 6},
       example{Point(0.5, -5, 0), Vector(0, 1, 0), 4, 6},
       example{Point(0.5, 0, 5), Vector(0, 0, -1), 4, 6},
       example{Point(0.5, 0, -5), Vector(0, 0, 1), 4, 6},
       example{Point(0, 0.5, 0), Vector(0, 0, 1), -1, 1}}));
  Point origin = std::get<0>(examples);
  Vector direction = std::get<1>(examples);
  double t1 = std::get<2>(examples);
  double t2 = std::get<3>(examples);

  Cube cube;
  Ray r(origin, direction);
  Intersections xs = cube.intersect(r);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(t1));
  REQUIRE(xs[1].t == Approx(t2));
}

TEST_CASE("A ray misses a cube", "[Sphere]") {
  // Examples:
  // | origin           | direction                      |
  // | point(-2, 0, 0)  | vector(0.2673, 0.5345, 0.8018) |
  // | point(0, -2, 0)  | vector(0.8018, 0.2673, 0.5345) |
  // | point(0, 0, -2)  | vector(0.5345, 0.8018, 0.2673) |
  // | point(2, 0, 2)   | vector(0, 0, -1)               |
  // | point(0, 2, 2)   | vector(0, -1, 0)               |
  // | point(2, 2, 0)   | vector(-1, 0, 0)               |

  using example = std::tuple<Point, Vector>;
  auto examples = GENERATE(table<Point, Vector>(
      {example{Point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018)},
       example{Point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345)},
       example{Point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673)},
       example{Point(2, 0, 2), Vector(0, 0, -1)},
       example{Point(0, 2, 2), Vector(0, -1, 0)},
       example{Point(2, 2, 0), Vector(-1, 0, 0)}}));
  Point origin = std::get<0>(examples);
  Vector direction = std::get<1>(examples);

  Cube cube;
  Ray r(origin, direction);
  Intersections xs = cube.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("The normal on the surface of a cube", "[Sphere]") {
  // Examples:
  // | point                | normal           |
  // | point(1, 0.5, -0.8)  | vector(1, 0, 0)  |
  // | point(-1, -0.2, 0.9) | vector(-1, 0, 0) |
  // | point(-0.4, 1, -0.1) | vector(0, 1, 0)  |
  // | point(0.3, -1, -0.7) | vector(0, -1, 0) |
  // | point(-0.6, 0.3, 1)  | vector(0, 0, 1)  |
  // | point(0.4, 0.4, -1)  | vector(0, 0, -1) |
  // | point(1, 1, 1)       | vector(1, 0, 0)  |
  // | point(-1, -1, -1)    | vector(-1, 0, 0) |

  using example = std::tuple<Point, Vector>;
  auto examples = GENERATE(
      table<Point, Vector>({example{Point(1, 0.5, -0.8), Vector(1, 0, 0)},
                            example{Point(-1, -0.2, 0.9), Vector(-1, 0, 0)},
                            example{Point(-0.4, 1, -0.1), Vector(0, 1, 0)},
                            example{Point(0.3, -1, -0.7), Vector(0, -1, 0)},
                            example{Point(-0.6, 0.3, 1), Vector(0, 0, 1)},
                            example{Point(0.4, 0.4, -1), Vector(0, 0, -1)},
                            example{Point(1, 1, 1), Vector(1, 0, 0)},
                            example{Point(-1, -1, -1), Vector(-1, 0, 0)}}));
  Point point = std::get<0>(examples);
  Vector expected_normal = std::get<1>(examples);

  Cube cube;
  Vector normal = cube.normal_at(point);
  REQUIRE_THAT(normal, Equals(expected_normal));
}
