#ifndef HITABLELISTH
#define HITABLELISTH

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable ** l, int n) { list = l; list_Size = n; }
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;
	Hitable **list;
	int list_Size;
};

bool HitableList::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	HitRecord temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_Size; i++)
	{
		if (list[i]->Hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif