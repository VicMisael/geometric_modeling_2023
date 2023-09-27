#pragma once
#include "Material.h"

class Mirror :
	public Material
{
	const float reflectivity_;

public:
	Mirror() : reflectivity_(1.0f) {};
	Mirror(float reflectivity) : reflectivity_(reflectivity >= 1.0f ? 1.0f : reflectivity)
	{
	};
	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection,
	               int32_t depth) const override;
};
