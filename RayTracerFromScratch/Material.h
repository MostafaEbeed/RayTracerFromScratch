#ifndef MATERIALH
#define MATERIALH

#include <iostream>
#include "Ray.h"
#include "Hitable.h"



Vec3 Reflect(const Vec3& v, const Vec3& n)
{
	return v - 2 * dot(v, n) * n;		  // Dot prodeuct of v and n gets the projection of v on a vector in the direction of n.
}

double D_Random()
{
	return ((double)rand() / (double)RAND_MAX);
}

Vec3 RandomInUnitSphere()
{
	Vec3 p;

	do
	{
		p = Vec3(D_Random(), D_Random(), D_Random());
	} while (p.Squared_Length() >= 1.0);
	return p;
}



class Material
{
public:
	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};


class Lambertian : public Material
{
public:
	Lambertian(const Vec3& a) : albedo(a) {}
	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 target = rec.p + rec.normal + RandomInUnitSphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}

	Vec3 albedo;
};


class Metal : public Material
{
public:
	Metal(const Vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 reflected = Reflect(Unit_Vector(r_in.Direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * RandomInUnitSphere());
		attenuation = albedo;
		return (dot(scattered.Direction(), rec.normal) > 0);
	}

	Vec3 albedo;
	float fuzz;
};




#endif