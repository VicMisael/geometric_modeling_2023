#include "Ray.h"

Vector3 Ray::point_at(float t) const
{
	return origin + direction * t;
}
