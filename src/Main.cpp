#include <iostream>

#include "Chapters/Chapter05.hpp"
#include "Chapters/Chapter06.hpp"
#include "Chapters/Chapter07.hpp"
#include "Chapters/Chapter09.hpp"
#include "Chapters/Extra/Ambient.hpp"
#include "Chapters/Extra/Colors.hpp"
#include "Chapters/Extra/Diffuse.hpp"
#include "Chapters/Extra/Shininess.hpp"
#include "Chapters/Extra/Specular.hpp"
#include "Chapters/Extra/SpheresOnSphere.hpp"

void run_chapters() {
  std::cout << "Running Chapter 5" << std::endl;
  chapter5();

  std::cout << "Running Chapter 6" << std::endl;
  chapter6();

  std::cout << "Running Chapter 7" << std::endl;
  chapter7();

  std::cout << "Running Chapter 9" << std::endl;
  chapter9();
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
  spheres_on_sphere();
}

int main() {
  std::cout << "Hello Raytracer" << std::endl;

  run_chapters();

  run_extra_materials();

  run_extra_scenes();
}
