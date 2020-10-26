#include "Core/Matrix.hpp"
#include "Scene/Objects/Group.hpp"
#include "Scene/Objects/Sphere.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("Creating a new group", "[Group]") {
  Group g;
  REQUIRE_THAT(g.transform(), Equals(Matrix::Identity));
  REQUIRE(g.objects().size() == 0);
}

TEST_CASE("An object has a parent attribute", "[Group]") {
  Sphere s;
  REQUIRE(s.parent() == nullptr);
}

TEST_CASE("Adding a child to a group", "[Group]") {
  Group g;
  Sphere s;
  g.add_child(&s);
  REQUIRE(g.objects().size() != 0);
  REQUIRE(g.objects()[0] == &s);
  REQUIRE(s.parent() == &g);
}

TEST_CASE("Intersecting a ray with an empty group", "[Group]") {
  Group g;
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Intersections xs = g.intersect(r);
  REQUIRE(xs.size() == 0);
}

TEST_CASE("Intersecting a ray with a nonempty group", "[Group]") {
  Group g;
  Sphere s1;
  g.add_child(&s1);

  Sphere s2;
  s2.set_transform(translation(0, 0, -3));
  g.add_child(&s2);

  Sphere s3;
  s3.set_transform(translation(5, 0, 0));
  g.add_child(&s3);

  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections xs = g.intersect(r);
  REQUIRE(xs.size() == 4);
  REQUIRE(xs[0].object == &s2);
  REQUIRE(xs[1].object == &s2);
  REQUIRE(xs[2].object == &s1);
  REQUIRE(xs[3].object == &s1);
}

TEST_CASE("Intersecting a transformed group", "[Group]") {
  Group g;
  g.set_transform(scaling(2));

  Sphere s;
  s.set_transform(translation(5, 0, 0));
  g.add_child(&s);

  Ray r(Point(10, 0, -10), Vector(0, 0, 1));
  Intersections xs = g.intersect(r);
  REQUIRE(xs.size() == 2);
}
