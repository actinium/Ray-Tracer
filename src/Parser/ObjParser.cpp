#include "ObjParser.hpp"

#include <cstdio>
#include <optional>

namespace {
std::optional<Point> parse_vertex(const std::string& line) {
  double x, y, z;
  int res = sscanf(line.c_str(), "v %lf %lf %lf", &x, &y, &z);
  if (res == 3) {
    return Point(x, y, z);
  }
  return {};
}
std::optional<Point> parse_face(const std::string& line) {}
}  // namespace

ObjParser::Obj ObjParser::parse_obj_file(std::istream& input) {
  ObjParser::Obj obj;
  std::string line;
  while (getline(input, line)) {
    if (std::optional<Point> vertex = parse_vertex(line); vertex.has_value()) {
      obj.vertices.push_back(*vertex);
    }
  }
  return obj;
}

Object* ObjParser::parse(std::istream&) { return nullptr; }
