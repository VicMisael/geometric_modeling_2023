#pragma once
#include "Material.h"
#include "../BxDF/Lambertian.h"

class Diffuse :
	public Material
{

public:
	const ColorVec color_;
	const Lambertian lambertian_;
	const ColorVec color;
	explicit Diffuse(const ColorVec& _color)
		: color_(_color) , lambertian_(Lambertian(1, _color))
	{
	}



	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override;
};
