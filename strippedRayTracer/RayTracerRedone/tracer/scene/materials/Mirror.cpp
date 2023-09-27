#include "Mirror.h"

#include "../World.h"
#include "../../utils/utility.h"


ColorVec Mirror::shade(const World& world, const Ray& ray, const intersectionRec& intersection, const int32_t depth) const
{
	const auto& hitPoint = intersection.hit_point;
	const Ray reflected(hitPoint, utility::reflect_vector(normalize(ray.direction), intersection.normal));
	return ColorVec(0.5,0.5,0.5)*(1-reflectivity_) + reflectivity_ * (world.trace_ray(reflected, depth - 1));

}
