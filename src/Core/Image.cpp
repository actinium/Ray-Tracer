#include "Image.hpp"

#include <algorithm>

#include "image_writer.h"

//------------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------------
Image::Image(std::size_t init_width, std::size_t init_height)
    : width_{init_width},
      height_{init_height},
      pixels_{new Color[init_width * init_height]} {}

Image::~Image() { delete[] pixels_; }

//------------------------------------------------------------------------------
// Save Image as PNG
//------------------------------------------------------------------------------
int Image::save_as_png(const std::string& filename) const {
  std::byte* data = to_byte_array();
  const char* c_str_filename = filename.c_str();
  int resp = stbi_write_png(c_str_filename, (int)width(), (int)height(), 3,
                            data, (int)width() * 3);
  delete[] data;
  return resp;
}

std::byte* Image::to_byte_array() const {
  std::byte* bytes = new std::byte[width_ * height_ * 3];
  int i = 0;
  for (std::size_t y = 0; y < height_; ++y) {
    for (std::size_t x = 0; x < width_; ++x) {
      int r = std::clamp(int(256 * get(x, y).red), 0, 255);
      int g = std::clamp(int(256 * get(x, y).green), 0, 255);
      int b = std::clamp(int(256 * get(x, y).blue), 0, 255);
      bytes[i++] = std::byte(r);
      bytes[i++] = std::byte(g);
      bytes[i++] = std::byte(b);
    }
  }
  return bytes;
}
