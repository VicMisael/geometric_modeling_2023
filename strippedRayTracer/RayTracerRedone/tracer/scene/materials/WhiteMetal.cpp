#include "WhiteMetal.h"


#include "../World.h"
#include "../../utils/utility.h"

ColorVec WhiteMetal::shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const
{
	const auto& hitPoint = intersection.hit_point;
	const auto reflected_vector = utility::reflect_vector(ray.direction, intersection.normal);
	const Ray reflected(hitPoint, reflected_vector+(fuzz_ * utility::random_in_unit_sphere()));

	return  0.8f*(world.trace_ray(reflected, depth - 1));
}
