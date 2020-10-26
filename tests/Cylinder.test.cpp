#include "Core/Intersection.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Objects/Cylinder.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("A ray misses a cylinder", "[Cylinder]") {
  // Examples:
  //  | origin          | direction       |
  //  | point(1, 0, 0)  | vector(0, 1, 0) |
  //  | point(0, 0, 0)  | vector(0, 1, 0) |
  //  | point(0, 0, -5) | vector(1, 1, 1) |

  using example = std::tuple<Point, Vector>;
  auto examples = GENERATE(
      table<Point, Vector>({example{Point(1, 0, 0), Vector(0, 1, 0)},
                            example{Point(0, 0, 0), Vector(0, 1, 0)},
                            example{Point(0, 0, -5), Vector(1, 1, 1)}}));

  Cylinder cyl;
  Point origin = std::get<0>(examples);
  Vector direction = normalize(std::get<1>(examples));
  Ray r(origin, direction);
  Intersections xs;
  cyl.intersect(r, xs);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray strikes a cylinder", "[Cylinder]") {
  // Examples:
  //  | origin            | direction         | t0      | t1      |
  //  | point(1, 0, -5)   | vector(0, 0, 1)   | 5       | 5       |
  //  | point(0, 0, -5)   | vector(0, 0, 1)   | 4       | 6       |
  //  | point(0.5, 0, -5) | vector(0.1, 1, 1) | 6.80798 | 7.08872 |

  using example = std::tuple<Point, Vector, double, double>;
  auto examples = GENERATE(table<Point, Vector, double, double>(
      {example{Point(1, 0, -5), Vector(0, 0, 1), 5, 5},
       example{Point(0, 0, -5), Vector(0, 0, 1), 4, 6},
       example{Point(0.5, 0, -5), Vector(0.1, 1, 1), 6.80798, 7.08872}}));

  Cylinder cyl;
  Point origin = std::get<0>(examples);
  Vector direction = normalize(std::get<1>(examples));
  double t0 = std::get<2>(examples);
  double t1 = std::get<3>(examples);
  Ray r(origin, direction);
  Intersections xs;
  cyl.intersect(r, xs);
  REQUIRE(xs.size() == 2);
  REQUIRE(xs[0].t == Approx(t0));
  REQUIRE(xs[1].t == Approx(t1));
}

TEST_CASE("Normal vector on a cylinder", "[Cylinder]") {
  // Examples:
  //  | point           | normal           |
  //  | point(1, 0, 0)  | vector(1, 0, 0)  |
  //  | point(0, 5, -1) | vector(0, 0, -1) |
  //  | point(0, -2, 1) | vector(0, 0, 1)  |
  //  | point(-1, 1, 0) | vector(-1, 0, 0) |

  using example = std::tuple<Point, Vector>;
  auto examples = GENERATE(
      table<Point, Vector>({example{Point(1, 0, 0), Vector(1, 0, 0)},
                            example{Point(0, 5, -1), Vector(0, 0, -1)},
                            example{Point(0, -2, 1), Vector(0, 0, 1)},
                            example{Point(-1, 1, 0), Vector(-1, 0, 0)}}));

  Point point = std::get<0>(examples);
  Vector normal = std::get<1>(examples);

  Cylinder cyl;
  Vector n = cyl.normal_at(point);
  REQUIRE_THAT(n, Equals(normal));
}

TEST_CASE("The default minimum and maximum for a cylinder", "[Cylinder]") {
  Cylinder cyl;
  REQUIRE(cyl.minimum == NEG_INF);
  REQUIRE(cyl.maximum == INF);
}

TEST_CASE("Intersecting a constrained cylinder", "[Cylinder]") {
  // Examples:
  //  |   | point             | direction         | count |
  //  | 1 | point(0, 1.5, 0)  | vector(0.1, 1, 0) | 0     |
  //  | 2 | point(0, 3, -5)   | vector(0, 0, 1)   | 0     |
  //  | 3 | point(0, 0, -5)   | vector(0, 0, 1)   | 0     |
  //  | 4 | point(0, 2, -5)   | vector(0, 0, 1)   | 0     |
  //  | 5 | point(0, 1, -5)   | vector(0, 0, 1)   | 0     |
  //  | 6 | point(0, 1.5, -2) | vector(0, 0, 1)   | 2     |

  using example = std::tuple<Point, Vector, int>;
  auto examples = GENERATE(table<Point, Vector, int>(
      {example{Point(0, 1.5, 0), Vector(0.1, 1, 0), 0},
       example{Point(0, 3, -5), Vector(0, 0, 1), 0},
       example{Point(0, 0, -5), Vector(0, 0, 1), 0},
       example{Point(0, 2, -5), Vector(0, 0, 1), 0},
       example{Point(0, 1, -5), Vector(0, 0, 1), 0},
       example{Point(0, 1.5, -2), Vector(0, 0, 1), 2}}));

  Point point = std::get<0>(examples);
  Vector direction = normalize(std::get<1>(examples));
  int count = std::get<2>(examples);

  Cylinder cyl;
  cyl.minimum = 1;
  cyl.maximum = 2;
  Ray r(point, direction);
  Intersections xs;
  cyl.intersect(r, xs);
  REQUIRE(xs.size() == count);
}

TEST_CASE("The default closed value for a cylinder", "[Cylinder]") {
  Cylinder cyl;
  REQUIRE(cyl.is_closed == false);
}

TEST_CASE("Intersecting the caps of a closed cylinder", "[Cylinder]") {
  // Examples:
  //  |   | point            | direction        | count |
  //  | 1 | point(0, 3, 0)   | vector(0, -1, 0) | 2     |
  //  | 2 | point(0, 3, -2)  | vector(0, -1, 2) | 2     |
  //  | 3 | point(0, 4, -2)  | vector(0, -1, 1) | 2     | # corner case
  //  | 4 | point(0, 0, -2)  | vector(0, 1, 2)  | 2     |
  //  | 5 | point(0, -1, -2) | vector(0, 1, 1)  | 2     | # corner case

  using example = std::tuple<Point, Vector, int>;
  auto examples = GENERATE(table<Point, Vector, int>(
      {example{Point(0, 3, 0), Vector(0, -1, 0), 2},
       example{Point(0, 3, -2), Vector(0, -1, 2), 2},
       example{Point(0, 4, -2), Vector(0, -1, 1), 2},
       example{Point(0, 0, -2), Vector(0, 1, 2), 2},
       example{Point(0, -1, -2), Vector(0, 1, 1), 2}}));

  Point point = std::get<0>(examples);
  Vector direction = normalize(std::get<1>(examples));
  int count = std::get<2>(examples);

  Cylinder cyl;
  cyl.minimum = 1;
  cyl.maximum = 2;
  cyl.is_closed = true;
  Ray r(point, direction);
  Intersections xs;
  cyl.intersect(r, xs);
  REQUIRE(xs.size() == count);
}

TEST_CASE("The normal vector on a cylinder's end caps", "[Cylinder]") {
  // Examples:
  //  | point            | normal           |
  //  | point(0, 1, 0)   | vector(0, -1, 0) |
  //  | point(0.5, 1, 0) | vector(0, -1, 0) |
  //  | point(0, 1, 0.5) | vector(0, -1, 0) |
  //  | point(0, 2, 0)   | vector(0, 1, 0)  |
  //  | point(0.5, 2, 0) | vector(0, 1, 0)  |
  //  | point(0, 2, 0.5) | vector(0, 1, 0)  |

  using example = std::tuple<Point, Vector>;
  auto examples = GENERATE(
      table<Point, Vector>({example{Point(0, 1, 0), Vector(0, -1, 0)},
                            example{Point(0.5, 1, 0), Vector(0, -1, 0)},
                            example{Point(0, 1, 0.5), Vector(0, -1, 0)},
                            example{Point(0, 2, 0), Vector(0, 1, 0)},
                            example{Point(0.5, 2, 0), Vector(0, 1, 0)},
                            example{Point(0, 2, 0.5), Vector(0, 1, 0)}}));

  Point point = std::get<0>(examples);
  Vector normal = std::get<1>(examples);

  Cylinder cyl;
  cyl.minimum = 1;
  cyl.maximum = 2;
  cyl.is_closed = true;
  Vector n = cyl.normal_at(point);
  REQUIRE_THAT(n, Equals(normal));
}
