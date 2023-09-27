#include "PerfectSpecular.h"
#include "../../utils/utility.h"
#include <glm/geometric.hpp>

ColorVec PerfectSpecular::rho(const Vector3& wo) const
{
	return Constants::BLACK;
}

ColorVec PerfectSpecular::f(const intersectionRec& intersection, const Vector3& wo, const Vector3& wi) const
{
	return Constants::BLACK;
}

sample_f_out PerfectSpecular::sample_f(const intersectionRec& intersection, const Vector3& wo) const
{
	
	const float ndotwo =dot(intersection.normal ,wo);
	const Vector3 wi = -wo + 2.0f * intersection.normal * ndotwo;
	const float pdf = fabs(dot(intersection.normal, wi));
	return { kr * cr,wi,pdf };
}
