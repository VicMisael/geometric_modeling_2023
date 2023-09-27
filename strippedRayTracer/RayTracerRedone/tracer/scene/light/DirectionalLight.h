#pragma once
#include "VectorialLight.h"

class DirectionalLight :public VectorialLight
{
	Vector3 direction_;
public:
	DirectionalLight() = delete;
	DirectionalLight(const Vector3 _direction, const float _intensity, const ColorVec _color) :
		VectorialLight(_intensity, _color), direction_(_direction)
	{}

	Vector3 getVector(const Point3) const override;
	Vector3 getVectorNormalized(const Point3) const override;
	ColorVec intensityAtPoint(const Point3) const override;
	bool shadow_hit(const World& world, const Ray& outgoing) const override;
};
