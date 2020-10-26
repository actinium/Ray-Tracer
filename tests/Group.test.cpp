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
  //  Then s.parent is nothing
}

TEST_CASE("Adding a child to a group", "[Group]") {
  Group g;
  Sphere s;
  //  When add_child(g, s)
  //  Then g is not empty
  //   And g includes s
  //   And s.parent = g
}
