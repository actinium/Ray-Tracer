#include "Core/Color.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Objects/Materials/Patterns/CheckerPattern.hpp"
#include "Scene/Objects/Materials/Patterns/GradientPattern.hpp"
#include "Scene/Objects/Materials/Patterns/RingPattern.hpp"
#include "Scene/Objects/Materials/Patterns/StripePattern.hpp"
#include "Scene/Objects/Sphere.hpp"
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

//------------------------------------------------------------------------------
// Pattern with Transformation
//------------------------------------------------------------------------------
TEST_CASE("Stripes with an object transformation", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);

  Sphere object;
  object.set_transform(scaling(2, 2, 2));

  StripePattern pattern(white, black);
  Color c = pattern.color_at_object(&object, Point(1.5, 0, 0));
  REQUIRE_THAT(c, Equals(white));
}

TEST_CASE("Stripes with a pattern transformation", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);

  Sphere object;

  StripePattern pattern(white, black);
  pattern.set_transform(scaling(2, 2, 2));
  Color c = pattern.color_at_object(&object, Point(1.5, 0, 0));
  REQUIRE_THAT(c, Equals(white));
}

TEST_CASE("Stripes with both an object and a pattern transformation",
          "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);

  Sphere object;
  object.set_transform(scaling(2, 2, 2));

  StripePattern pattern(white, black);
  pattern.set_transform(scaling(0.5, 0, 0));
  Color c = pattern.color_at_object(&object, Point(2.5, 0, 0));
  REQUIRE_THAT(c, Equals(white));
}

TEST_CASE("The default pattern transformation", "[Pattern]") {
  TestPattern pattern;
  REQUIRE_THAT(pattern.transform(), Equals(Matrix::Identity));
}

TEST_CASE("Assigning a transformation", "[Pattern]") {
  TestPattern pattern;
  pattern.set_transform(translation(1, 2, 3));
  REQUIRE_THAT(pattern.transform(), Equals(translation(1, 2, 3)));
}

TEST_CASE("A pattern with an object transformation", "[Pattern]") {
  Sphere shape;
  shape.set_transform(scaling(2, 2, 2));
  TestPattern pattern;
  Color c = pattern.color_at_object(&shape, Point(2, 3, 4));
  REQUIRE_THAT(c, Equals(Color(1, 1.5, 2)));
}

TEST_CASE("A pattern with a pattern transformation", "[Pattern]") {
  Sphere shape;
  TestPattern pattern;
  pattern.set_transform(scaling(2, 2, 2));
  Color c = pattern.color_at_object(&shape, Point(2, 3, 4));
  REQUIRE_THAT(c, Equals(Color(1, 1.5, 2)));
}

TEST_CASE("A pattern with both an object and a pattern transformation",
          "[Pattern]") {
  Sphere shape;
  shape.set_transform(scaling(2, 2, 2));
  TestPattern pattern;
  pattern.set_transform(translation(0.5, 1, 1.5));
  Color c = pattern.color_at_object(&shape, Point(2.5, 3, 3.5));
  REQUIRE_THAT(c, Equals(Color(0.75, 0.5, 0.25)));
}

//------------------------------------------------------------------------------
// Gradient Pattern
//------------------------------------------------------------------------------
TEST_CASE("A gradient linearly interpolates between colors", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  GradientPattern pattern(white, black);
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0.25, 0, 0)),
               Equals(Color(0.75, 0.75, 0.75)));
  REQUIRE_THAT(pattern.color_at(Point(0.5, 0, 0)),
               Equals(Color(0.5, 0.5, 0.5)));
  REQUIRE_THAT(pattern.color_at(Point(0.75, 0, 0)),
               Equals(Color(0.25, 0.25, 0.25)));
}

//------------------------------------------------------------------------------
// Ring Pattern
//------------------------------------------------------------------------------
TEST_CASE("A ring should extend in both x and z", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  RingPattern pattern(white, black);
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(1, 0, 0)), Equals(black));
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 1)), Equals(black));
  REQUIRE_THAT(pattern.color_at(Point(0.708, 0, 0.708)), Equals(black));
}

//------------------------------------------------------------------------------
// Checker Pattern
//------------------------------------------------------------------------------
TEST_CASE("Checkers should repeat in x", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  CheckerPattern pattern(white, black);
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0.99, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(1.01, 0, 0)), Equals(black));
}

TEST_CASE("Checkers should repeat in y", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  CheckerPattern pattern(white, black);
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 0.99, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 1.01, 0)), Equals(black));
}

TEST_CASE("Checkers should repeat in z", "[Pattern]") {
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  CheckerPattern pattern(white, black);
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 0.99)), Equals(white));
  REQUIRE_THAT(pattern.color_at(Point(0, 0, 1.01)), Equals(black));
}
