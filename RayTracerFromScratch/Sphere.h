#ifndef SPHEREH
#define SPHEREH
#include "Hitable.h"


class Sphere : public Hitable
{
public:
	Sphere() {}
	Sphere(Vec3 cen, float r, Material * mat) : center(cen), radius(r), _material(mat) {};
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
	Vec3 center;
	float radius;
	Material * _material;
};

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = dot(oc, r.Direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a *c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = _material;
			return true;
		}
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = _material;
			return true;
		}
	}
	return false;
}

#endif