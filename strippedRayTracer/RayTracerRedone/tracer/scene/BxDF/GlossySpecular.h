#pragma once 
#include "BxDF.h"

/**
 * Based on ray tracing from groundUP
 */
class GlossySpecular :
	public BxDF
	
{//controls how bright the specular highlight
	const float ks_;
	//specular reflection color
	const ColorVec color_;
	//As e increases, the highlights become smaller, and the spheres look more shiny
	const float exp_;
public:
	GlossySpecular() = delete;
	GlossySpecular(const float ks, const float exp) :GlossySpecular(ks, { 1,1,1 }, exp){};
	GlossySpecular(const float ks, const ColorVec color, const float exp) :ks_(ks), color_(color), exp_(exp){};
	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersectionRec& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f_out sample_f(const intersectionRec& intersection, const Vector3& wo) const override;

    sample_f_out sample_f(const intersectionRec &intersection, const Vector3 &wo, const Vector3 &wi) const override;
};
