#pragma once

#include <cstddef>
#include <string>

#include "Core/Color.hpp"

//------------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------------
class Image {
 public:
  Image(std::size_t init_width, std::size_t init_height);
  Image(std::size_t init_width, std::size_t init_height, const Color& color);
  Image(const Image& other);
  ~Image();

 public:
  std::size_t width() const { return width_; }
  std::size_t height() const { return height_; }

  Color& operator()(std::size_t x, std::size_t y) { return get(x, y); }

  const Color& operator()(std::size_t x, std::size_t y) const {
    return get(x, y);
  }

  void write(std::size_t x, std::size_t y, const Image& image);

  int save_as_png(const std::string& filename) const;

 private:
  Color& get(std::size_t x, std::size_t y) { return pixels_[x + y * width_]; }

  const Color& get(std::size_t x, std::size_t y) const {
    return pixels_[x + y * width_];
  }

  std::byte* to_byte_array() const;

 private:
  std::size_t width_;
  std::size_t height_;
  Color* pixels_;
};
