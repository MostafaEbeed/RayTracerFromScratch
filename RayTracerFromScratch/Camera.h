#ifndef CAMERAH
#define CAMERAH
#include "Ray.h"


class Camera
{
public:
	Camera()
	{
		lower_Left_Corner = Vec3(-2.0, -1.0, -1.0);
		horizontal = Vec3(4.0, 0.0, 0.0);
		vertical = Vec3(0.0, 2.0, 0.0);
		origin = Vec3(0.0, 0.0, 0.0);
	}
	Ray GetRay(float u, float v) { return Ray(origin, lower_Left_Corner + u * horizontal + v * vertical - origin); }

	Vec3 origin;
	Vec3 lower_Left_Corner;
	Vec3 horizontal;
	Vec3 vertical;
};

#endif
