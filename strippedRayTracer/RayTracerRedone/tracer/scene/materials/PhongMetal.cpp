#include "PhongMetal.h"

#include "../World.h"
#include "../../utils/utility.h"

ColorVec PhongMetal::shade(const World& world, const Ray& ray, const intersectionRec& intersection,
	int32_t depth) const
{
	ColorVec L= Phong::shade(world, ray, intersection, depth);

	const auto wo = -ray.direction;
	const auto [color, wi, pdf] = metallic_brdf.sample_f(intersection, wo);
	const Ray reflected(intersection.hit_point, wi);

	L += color*world.trace_ray(reflected, depth - 1) * dot(intersection.normal, wi) / pdf;
	return L;

}
