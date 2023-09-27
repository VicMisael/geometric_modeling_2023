#pragma once
#include "Phong.h"
#include "../BxDF/MetallicSpecular.h"
class PhongMetal :
    public Phong
{
	float fuzz_;
	MetallicSpecular metallic_brdf;
public:
	PhongMetal(const ColorVec color,const float fuzz,const float kreflective,const float kdiffuse,const float exp):
	Phong(color, kdiffuse, exp), fuzz_(fuzz), metallic_brdf(kreflective, fuzz)
	{
		
	}

	PhongMetal(ColorVec color,float fuzz) : PhongMetal(color, fuzz, 1, 0.1, 25)
	{
	}
	PhongMetal(float fuzz) : PhongMetal(Constants::BLACK,fuzz,1,0.1,25)
	{
	}
	PhongMetal() : PhongMetal(1) {}

	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override;

};

