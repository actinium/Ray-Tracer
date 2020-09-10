#include "Chapter06.hpp"

#include "Core/Color.hpp"
#include "Core/Image.hpp"
#include "Core/Lighting.hpp"
#include "Core/Math.hpp"
#include "Core/Point.hpp"
#include "Core/Ray.hpp"
#include "Core/Transformations.hpp"
#include "Scene/Lights/Light.hpp"
#include "Scene/Objects/Materials/SimpleMaterial.hpp"
#include "Scene/Objects/Sphere.hpp"

namespace {
Image render_sphere(const std::size_t img_pixels, const Sphere& shape) {
  const Point ray_origin(0, 0, -5);
  const double wall_z = 10;
  const double wall_size = 7;
  const double half = wall_size / 2;
  const double pixel_size = wall_size / img_pixels;

  Light light(Point(-10, 10, -10), Color(1, 1, 1));

  Image image(img_pixels, img_pixels);

  for (std::size_t y = 0; y < img_pixels; ++y) {
    double world_y = half - pixel_size * y;
    for (std::size_t x = 0; x < img_pixels; ++x) {
      double world_x = -half + pixel_size * x;
      Point position(world_x, world_y, wall_z);
      Ray r(ray_origin, normalize(position - ray_origin));
      Intersections xs = shape.intersect(r);
      Hit hit = get_first_hit(xs);
      if (hit.has_value()) {
        Point point = r.position(hit->t);
        Vector normal = hit->object->normal_at(point);
        Vector eye = -r.direction;
        Color color = lighting(hit->object->material(), hit->object, light,
                               point, eye, normal, false);
        image(x, y) = color;
      }
    }
  }
  return image;
}
}  // namespace

void chapter6() {
  const std::size_t img_pixels = 400;

  Image image(10 + 2 * (10 + img_pixels), 10 + 2 * (10 + img_pixels),
              Color::White);

  Sphere shape1;
  SimpleMaterial material1;
  material1.color = Color::Orange;
  shape1.set_material(&material1);
  shape1.set_transform(scaling(0.7, 0.7, 0.7));
  Image image1 = render_sphere(img_pixels, shape1);
  image.write(10, 10, image1);

  Sphere shape2;
  SimpleMaterial material2;
  material2.color = Color::Green;
  shape2.set_material(&material2);
  shape2.set_transform(scaling(1, 0.5, 1));
  Image image2 = render_sphere(img_pixels, shape2);
  image.write(img_pixels + 20, 10, image2);

  Sphere shape3;
  SimpleMaterial material3;
  material3.color = Color::Blue;
  shape3.set_material(&material3);
  shape3.set_transform(shearing(0, 0.5, 0, 0.7, 0, 0) * scaling(0.7, 0.4, 0.7));
  Image image3 = render_sphere(img_pixels, shape3);
  image.write(10, img_pixels + 20, image3);

  Sphere shape4;
  SimpleMaterial material4;
  material4.color = Color::Yellow;
  shape4.set_material(&material4);
  shape4.set_transform(translation(0.3, -0.3, 0.3) * scaling(0.4, 0.4, 0.4));
  Image image4 = render_sphere(img_pixels, shape4);
  image.write(img_pixels + 20, img_pixels + 20, image4);

  image.save_as_png("images/chapter-06-light-and-shading.png");
}
