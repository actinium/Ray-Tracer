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

Image::Image(std::size_t init_width, std::size_t init_height,
             const Color& color)
    : Image(init_width, init_height) {
  for (std::size_t i = 0; i < init_width * init_height; ++i) {
    pixels_[i] = color;
  }
}

Image::Image(const Image& other)
    : width_{other.width()},
      height_{other.height()},
      pixels_{new Color[other.width() * other.height()]} {
  std::copy(other.pixels_, other.pixels_ + other.width() * other.height(),
            pixels_);
}

Image::~Image() { delete[] pixels_; }

void Image::write(std::size_t x_start, std::size_t y_start,
                  const Image& image) {
  for (std::size_t x = 0; x < image.width(); ++x) {
    for (std::size_t y = 0; y < image.height(); ++y) {
      get(x_start + x, y_start + y) = image(x, y);
    }
  }
}

//------------------------------------------------------------------------------
// Save Image as PNG
//------------------------------------------------------------------------------
int Image::save_as_png(const std::string& filename) const {
  std::byte* data = to_byte_array();
  const char* c_str_filename = filename.c_str();
  int resp = stbi_write_png(c_str_filename, static_cast<int>(width()),
                            static_cast<int>(height()), 3, data,
                            static_cast<int>(width()) * 3);
  delete[] data;
  return resp;
}

std::byte* Image::to_byte_array() const {
  std::byte* bytes = new std::byte[width_ * height_ * 3];
  int i = 0;
  for (std::size_t y = 0; y < height_; ++y) {
    for (std::size_t x = 0; x < width_; ++x) {
      int r = std::clamp(static_cast<int>(256 * get(x, y).r), 0, 255);
      int g = std::clamp(static_cast<int>(256 * get(x, y).g), 0, 255);
      int b = std::clamp(static_cast<int>(256 * get(x, y).b), 0, 255);
      bytes[i++] = std::byte(r);
      bytes[i++] = std::byte(g);
      bytes[i++] = std::byte(b);
    }
  }
  return bytes;
}
