#include "PhongReflective.h"
#include <glm/geometric.hpp>
#include "../World.h"

ColorVec PhongReflective::shade(const World& world, const Ray& ray, const intersectionRec& intersection,
                                int32_t depth) const
{
	ColorVec L = Phong::shade(world, ray, intersection, depth);
	const auto wo = -1.0f* ray.direction;
	const auto [color,wi,pdf] = reflective_brdf.sample_f(intersection, wo);
	const Ray reflected(intersection.hit_point, wi);

	L += color*world.trace_ray(reflected, depth - 1) * dot(intersection.normal, wi) / pdf;
	return L;
}
