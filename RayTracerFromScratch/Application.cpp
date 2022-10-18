#include <iostream>
#include "Sphere.h"
#include "HitableList.h"
#include <limits>
#include "Camera.h"
#include "Material.h"
#include <stdlib.h>

#define MAXFLOAT 3.40282e+038

/*
Vec3 RandomInUnitSphere()
{
	double d_random = (double)rand() / (double)RAND_MAX;
	Vec3 p;
	do
	{
		p = 2.0 * Vec3(((double)rand() / (double)RAND_MAX)
			, ((double)rand() / (double)RAND_MAX)
			, ((double)rand() / (double)RAND_MAX)) - Vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}
*/

Vec3 Color(const Ray& r, Hitable *world, int depth)
{
	HitRecord rec;
	if (world->Hit(r, 0.001, MAXFLOAT, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else
	{
		Vec3 unit_direction = Unit_Vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0); // scales form 0 to 1 instead of from -1 to 1
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0); // does a lerp from white to blue
	}
}

int main()
{
	const auto aspect_ratio = 16.0 / 9.0;
	const int nx = 1200;
	const int ny = 100;
	const int image_height = static_cast<int>(nx / aspect_ratio);
	int ns = 100;  // num of samples per pixel
	std::cout << "P3\n" << nx << " " << image_height << "\n255\n";

	Hitable *list[4];
	list[0] = new Sphere(Vec3( 0.0,    0.0, -1.5), 0.5, new Lambertian(Vec3(1.0, 0.1, 0.1)));
	list[1] = new Sphere(Vec3( 0.0, -100.5, -1), 100, new Lambertian(Vec3(0.1, 0.1, 1.0)));
	list[2] = new Sphere(Vec3( 1.0,    0.0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.3));
	list[3] = new Sphere(Vec3(-1.0,    0.0, -1), 0.5, new Metal(Vec3(0.8, 0.8, 0.8), 1.0));
	Hitable *world = new HitableList(list, 4);

	Camera cam;

	for (int j = image_height -1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; ++s)
			{
				float u = float((i + D_Random()) / float(nx - 1));
				float v = float((j + D_Random()) / float(image_height - 1));
				Ray r = cam.GetRay(u, v);
				Vec3 p = r.PointAtParameter(2.0);
				col += Color(r, world, 0);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}