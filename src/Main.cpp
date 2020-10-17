#include <iostream>

#include "Chapters/Chapters.hpp"
#include "Chapters/Extra/Extras.hpp"
#include "Core/Constants.hpp"

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

  std::cout << "Running Chapter 12" << std::endl;
  chapter12();

  std::cout << "Running Chapter 13" << std::endl;
  chapter13();
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

  std::cout << MAX_THREADS << " concurrent threads are supported.\n\n";

  run_chapters();
  run_extra_materials();
  run_extra_scenes();
}
