#include "Core/Color.hpp"
#include "Scene/Objects/Materials/Patterns/StripePattern.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

//------------------------------------------------------------------------------
// Stripe Pattern
//------------------------------------------------------------------------------
TEST_CASE("A stripe pattern is constant in y", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  StripePattern pattern(white, black);

  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 1, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 2, 0)), Equals(white));
}

TEST_CASE("A stripe pattern is constant in z", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  StripePattern pattern(white, black);

  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 1)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 2)), Equals(white));
}

TEST_CASE("A stripe pattern alternates in x", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  StripePattern pattern(white, black);

  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0.9, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(1, 0, 0)), Equals(black));
  REQUIRE_THAT(pattern.color_at(Point(-0.1, 0, 0)), Equals(black));
  REQUIRE_THAT(pattern.color_at(Point(-1, 0, 0)), Equals(black));
  REQUIRE_THAT(pattern.color_at(Point(-1.1, 0, 0)), Equals(white));
}
