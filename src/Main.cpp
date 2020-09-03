#include <iostream>

#include "Chapters/Chapter05.hpp"
#include "Chapters/Chapter06.hpp"
#include "Chapters/Chapter07.hpp"
#include "Chapters/Chapter09.hpp"

int main() {
  std::cout << "Hello Raytracer" << std::endl;

  std::cout << "Running Chapter 5" << std::endl;
  chapter5();

  std::cout << "Running Chapter 6" << std::endl;
  chapter6();

  std::cout << "Running Chapter 7-8" << std::endl;
  chapter7();

  std::cout << "Running Chapter 9" << std::endl;
  chapter9();
}
