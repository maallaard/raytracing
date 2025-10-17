#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = center - r.origin();

    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - (radius * radius);

    double discriminant = (h * h) - (4 * a * c);

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-h - std::sqrt(discriminant)) / a;
    }
}

color ray_color(const ray &r)
{
    double t = hit_sphere(point3(0, 0, -1), 0.5, r);

    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    /* Image */

    // Set aspect ratio to 16:9.
    double aspect_ratio = 16.0 / 9.0;

    // Set image width to 400 pixels.
    int image_width = 400;

    // Calculate image height based on it's width.
    int image_height = int(image_width / aspect_ratio);

    // Ensure image height is at least 1.
    if (image_height < 1)
    {
        image_height = 1;
    }

    /* Viewport */

    // Set focal length.
    double viewport_focal_length = 1.0;

    // Set viewport height.
    double viewport_height = 2.0;

    // Calculate viewport width based on it's height.
    double viewport_width = viewport_height * (double(image_width) / image_height);

    // Calculate vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Set viewport's center coordinates.
    vec3 viewport_center = vec3(0, 0, 0);

    // Calculate horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate location of top-leftmost pixel.
    vec3 viewport_top_left = viewport_center - vec3(0, 0, viewport_focal_length) - (viewport_u / 2) - (viewport_v / 2);

    vec3 pixel00_loc = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    /* Render */

    // Write .ppm header information.
    write_header(std::cout, image_width, image_height);

    // Iterate through each pixel left-to-right and top-to-bottom.
    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++)
        {
            vec3 pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);

            vec3 ray_direction = pixel_center - viewport_center;
            ray r(viewport_center, ray_direction);

            // Set pixel color for current pixel.
            color pixel_color = ray_color(r);

            // Write pixel RGB bytes to .ppm file.
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
