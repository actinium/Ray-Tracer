#include <sstream>
#include <string>

#include "Parser/ObjParser.hpp"
#include "TestUtils.hpp"
#include "catch.hpp"

TEST_CASE("Ignoring unrecognized lines", "[Obj-Parser]") {
  std::string gibberish =
      "There was a young lady named Bright\n"
      "who traveled much faster than light.\n"
      "She set out one day\n"
      "in a relative way,\n"
      "and came back the previous night.";
  std::stringstream gibberish_input(gibberish);

  ObjParser parser;
  ObjParser::Obj obj = parser.parse_obj_file(gibberish_input);

  REQUIRE(gibberish_input.eof());
  REQUIRE(obj.vertices.size() == 0);
}

TEST_CASE("Vertex records", "[Obj-Parser]") {
  std::string file =
      "There was a young lady named Bright\n"
      "who traveled much faster than light.\n"
      "v -1 1 0\n"
      "v -1.0000 0.5000 0.0000\n"
      "She set out one day\n"
      "in a relative way,\n"
      "v 1 0 0\n"
      "v 1 1 0\n"
      "and came back the previous night.";
  std::stringstream input(file);

  ObjParser parser;
  ObjParser::Obj obj = parser.parse_obj_file(input);

  REQUIRE(input.eof());
  REQUIRE(obj.vertices.size() == 4);
  REQUIRE_THAT(obj.vertices[0], Equals(Point(-1, 1, 0)));
  REQUIRE_THAT(obj.vertices[1], Equals(Point(-1, 0.5, 0)));
  REQUIRE_THAT(obj.vertices[2], Equals(Point(1, 0, 0)));
  REQUIRE_THAT(obj.vertices[3], Equals(Point(1, 1, 0)));
}
