#pragma once
#include "../utils/Types.h"
class Ray
{
public:
	const Point3 origin;
	const Vector3 direction;
	Ray(Point3 _origin, Vector3 _direction) :origin(_origin), direction(_direction) {};

	Point3 point_at(float t) const;
};

