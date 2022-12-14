#ifndef HITABLEH
#define HITABLEH
#include "Ray.h"


class Material;


struct HitRecord
{
	float t;
	Vec3 p;
	Vec3 normal;
	Material * mat_ptr;
};


class Hitable
{
public:
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};
#endif