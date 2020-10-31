#pragma once

#include <istream>

class Object;

class ObjParser {
  Object* parse(std::istream& input);
};
