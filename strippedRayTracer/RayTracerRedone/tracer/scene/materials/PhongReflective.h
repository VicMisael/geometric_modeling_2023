#pragma once
#include "Phong.h"
#include "../BxDF/PerfectSpecular.h"
class PhongReflective :
    public Phong
{
	PerfectSpecular reflective_brdf;
public:
	PhongReflective() :Phong(Constants::BLACK, Constants::WHITE, 1, 1, 25), reflective_brdf(1) {};
	PhongReflective( const ColorVec color, const float ks, const float exp,const float reflectance):
		Phong(color, ks, exp), reflective_brdf(reflectance) {};
	PhongReflective(const ColorVec color, const float ks,const float kd, const float exp, const float reflectance) :
		Phong( color,  ks, kd,  exp), reflective_brdf(reflectance) {};

	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override;
};

