#pragma once
#include "Material.h"
#include "../BxDF/Lambertian.h"
class Matte :
    public Material
{
	const Lambertian brdf_;
public:
	Matte(const float kd,const ColorVec albedo):brdf_(Lambertian(kd,albedo)){}
	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override;
};

