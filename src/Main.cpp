#include <iostream>

#include "Chapters/Chapters.hpp"
#include "Chapters/Extra/Extras.hpp"

void run_chapters() {
  std::cout << "Running Chapter 5" << std::endl;
  chapter5();

  std::cout << "Running Chapter 6" << std::endl;
  chapter6();

  std::cout << "Running Chapter 7" << std::endl;
  chapter7();

  std::cout << "Running Chapter 9" << std::endl;
  chapter9();

  std::cout << "Running Chapter 10" << std::endl;
  chapter10();

  std::cout << "Running Chapter 11" << std::endl;
  chapter11();
}

void run_extra_materials() {
  std::cout << "Running Extra - Colors" << std::endl;
  extra_colors();

  std::cout << "Running Extra - Ambient" << std::endl;
  extra_ambient();

  std::cout << "Running Extra - Diffuse" << std::endl;
  extra_diffuse();

  std::cout << "Running Extra - Specular" << std::endl;
  extra_specular();

  std::cout << "Running Extra - Shininess" << std::endl;
  extra_shininess();
}

void run_extra_scenes() {
  std::cout << "Running Extra - Spheres on Sphere" << std::endl;
  extra_spheres_on_sphere();
}

int main() {
  std::cout << "Hello Raytracer" << std::endl;

  run_chapters();

  run_extra_materials();

  run_extra_scenes();
}
