#pragma once
#include "BxDF.h"

class PerfectSpecular :
    public BxDF
{
	const ColorVec cr = Constants::WHITE;
	const float kr;
public:
	PerfectSpecular(const float kr_):kr(kr_){}

	ColorVec rho(const Vector3& wo) const override;
	ColorVec f(const intersectionRec& intersection, const Vector3& wo, const Vector3& wi) const override;
	::sample_f_out sample_f(const intersectionRec& intersection, const Vector3& wo) const override;
};

