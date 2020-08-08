#include "Core/Color.hpp"
#include "Core/Image.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("Image construction", "[Image]") {
  Image img(20, 10);
  REQUIRE(img.width() == 20);
  REQUIRE(img.height() == 10);
  for (std::size_t w = 0; w < img.width(); ++w) {
    for (std::size_t h = 0; h < img.height(); ++h) {
      REQUIRE_THAT(img(w, h), Equals(Color(0, 0, 0)));
    }
  }
}

TEST_CASE("Assigning colors to an image", "[Image]") {
  Image img(10, 10);

  img(1, 1) = Color(0.1, 0.2, 0.3);
  img(1, 2) = Color(0.2, 0.3, 0.4);
  img(2, 1) = Color(0.3, 0.4, 0.5);
  REQUIRE_THAT(img(1, 1), Equals(Color(0.1, 0.2, 0.3)));
  REQUIRE_THAT(img(1, 2), Equals(Color(0.2, 0.3, 0.4)));
  REQUIRE_THAT(img(2, 1), Equals(Color(0.3, 0.4, 0.5)));

  img(9, 2) = Color::Purple;
  img(9, 3) = Color::Lightgrey;
  img(9, 4) = Color::Yellow;
  REQUIRE_THAT(img(9, 2), Equals(Color::Purple));
  REQUIRE_THAT(img(9, 3), Equals(Color::Lightgrey));
  REQUIRE_THAT(img(9, 4), Equals(Color::Yellow));
}
