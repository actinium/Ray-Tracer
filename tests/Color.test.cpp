#include "Core/Color.hpp"
#include "Core/Math.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("The default color is (0, 0, 0)", "[Color]") {
  Color c;
  REQUIRE(c.red == Approx(0));
  REQUIRE(c.green == Approx(0));
  REQUIRE(c.blue == Approx(0));
}

TEST_CASE("Color cunstruction", "[Color]") {
  Color c(1, 0.5, 0);
  REQUIRE(c.red == Approx(1));
  REQUIRE(c.green == Approx(0.5));
  REQUIRE(c.blue == Approx(0));
}

TEST_CASE("Color cunstruction with hex values", "[Color]") {
  REQUIRE_THAT(Color("000000"), Equals(Color(0, 0, 0)));
  REQUIRE_THAT(Color("FF0000"), Equals(Color(1, 0, 0)));
  REQUIRE_THAT(Color("00FF00"), Equals(Color(0, 1, 0)));
  REQUIRE_THAT(Color("0000FF"), Equals(Color(0, 0, 1)));
  REQUIRE_THAT(Color("FFFFFF"), Equals(Color(1, 1, 1)));
  REQUIRE_THAT(Color("ABCDEF"), Equals(Color(0.670588, 0.803922, 0.937255)));
}

//------------------------------------------------------------------------------
// Addition
//------------------------------------------------------------------------------
TEST_CASE("Adding two colors", "[Color]") {
  REQUIRE_THAT(Color(2.3, 0, -3.0) + Color(0, -1, 5.6),
               Equals(Color(2.3, -1, 2.6)));
}

//------------------------------------------------------------------------------
// Subtraction
//------------------------------------------------------------------------------
TEST_CASE("Subtracting a color from a color", "[Color]") {
  REQUIRE_THAT(Color(2.3, 0, -3.0) - Color(0, -1, 5.6),
               Equals(Color(2.3, 1, -8.6)));
}

//------------------------------------------------------------------------------
// Scalar Multiplication
//------------------------------------------------------------------------------
TEST_CASE("Multiplying a color by a scalar", "[Color]") {
  REQUIRE_THAT(2 * Color(0.2, 0.3, 0.4), Equals(Color(0.4, 0.6, 0.8)));
  REQUIRE_THAT(Color(0.2, 0.3, 0.4) * 2, Equals(Color(0.4, 0.6, 0.8)));
}

//------------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------------
TEST_CASE("Multiplying two colors", "[Color]") {
  REQUIRE_THAT(Color(1, 0.2, 0.4) * Color(0.9, 1, 0.1),
               Equals(Color(0.9, 0.2, 0.04)));
}
