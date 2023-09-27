#pragma once
#include "Material.h"

class WhiteMetal:public Material
{
	float fuzz_;
public:
	WhiteMetal() :fuzz_(1.0f){}
	WhiteMetal(float fuzz) :fuzz_(fuzz >= 1.0f ? 1.0f : fuzz)
	{
		
	}
	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override;
};

