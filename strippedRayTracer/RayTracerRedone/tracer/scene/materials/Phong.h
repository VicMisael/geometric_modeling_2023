#pragma once
#include "Material.h"
#include "../BxDF/Lambertian.h"
#include "../BxDF/GlossySpecular.h"
class Phong :
    public Material
{
	const Lambertian lambertian_;
	const GlossySpecular glossy_specular_;
public:
	Phong(const ColorVec color,const ColorVec specular_color,
		const float kspecular, const float kdiffuse, const float exp) :lambertian_(kdiffuse, color), glossy_specular_(kspecular, specular_color, exp) {};

	Phong(const ColorVec color,const float kspecular,const float kdiffuse,const float exp):lambertian_(kspecular,color),glossy_specular_(kdiffuse,exp){};
	
	Phong(const ColorVec color, const float kspecular, const float exp) :lambertian_(1.0f, color), glossy_specular_(kspecular, exp) {};

	ColorVec shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const override;

    ColorVec &getVec(const World &world, const intersectionRec &intersection, const Vector3 &wo, ColorVec &L) const;
};

