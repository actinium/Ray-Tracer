#pragma once

#include <istream>
#include <vector>

#include "Core/Point.hpp"

class Object;

class ObjParser {
 public:
  struct Obj {
    std::vector<Point> vertices;
  };
  Obj parse_obj_file(std::istream& input);

 public:
  Object* parse(std::istream& input);
};
