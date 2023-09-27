#pragma once
#include "VectorialLight.h"
class PointLight:public VectorialLight
{
	Vector3 point;
public:
	PointLight() = delete;
	PointLight(const Vector3 _point, const float _intensity, const ColorVec _color) :
		VectorialLight(_intensity, _color), point(_point)
	{}

	ColorVec intensityAtPoint( const Point3) const override;
	Vector3 getVector(const Point3) const override;
	Vector3 getVectorNormalized(const Point3) const override;
	bool shadow_hit(const World& world, const Ray& outgoing) const override;
};

