#pragma once
#include "Light.h"

class World;
class Ray;

class VectorialLight :public Light
{
protected:
	const bool cast_shadow = true;
public:
	VectorialLight(const float _intensity, const ColorVec _color) : Light(_intensity, _color) {};
	virtual Vector3 getVector(const Point3) const = 0;
	virtual Vector3 getVectorNormalized(const Point3) const = 0;
	virtual ColorVec intensityAtPoint(const Point3) const = 0;
	virtual bool casts_shadow() const
	{
		return cast_shadow;
	}
	virtual bool shadow_hit(const World& world, const Ray &outgoing) const = 0;
};

