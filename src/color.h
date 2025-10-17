#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ray.h"

#include <iostream>

using color = vec3;

color ray_color(const ray &r)
{
    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

void write_header(std::ostream &out, const int &image_width, const int &image_height)
{
    out << "P3\n";
    out << image_width << ' ' << image_height << '\n';
    out << "255\n";
}

void write_color(std::ostream &out, const color &pixel_color)
{
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
