#include "Diffuse.h"

#include "../../utils/utility.h"
#include "../../utils/Constants.h"
#include "../World.h"



inline bool nearzero(const Vector3 v)
{
	return v.x < Constants::EPSILON && v.y < Constants::EPSILON && v.z < Constants::EPSILON;
}

inline std::optional<Ray> scatter(const Ray& in, const intersectionRec& intersection)
{
	const auto normal = intersection.normal;
	auto out_dir = normal + utility::random_in_unit_sphere();
	if (nearzero(out_dir))
	{
		out_dir = normal;
	}
	auto scattered = Ray(intersection.hit_point, out_dir);
	return scattered;
}

// Antes eu e Deus sabiam o que esse c�digo fazia
// agora s� Deus

ColorVec oldshading(const Diffuse &diff, const World& world, const Ray& ray, const intersectionRec& intersection, const int32_t depth)
{
	const auto& intensity_at_point = world.getAmbientLight().intensityAtPoint(intersection.hit_point);
	const auto& ambient_intensity = intensity_at_point * (diff.color_);
	const auto& out = scatter(ray, intersection);

	if (out)
	{
		const Ray result = out.value();
		auto out = world.trace_ray(result, depth - 1);
		out.clamp_to_x_if_bigger_than(3, 2);
		return ambient_intensity + 0.5f * out * diff.color_;
	}
	return ambient_intensity;
}

ColorVec new_shading(const Diffuse &diff, const World& world, const Ray& ray, const intersectionRec& intersection, const int32_t depth)
{
	const Vector3 wo = -ray.direction;
	const auto [color, wi, pdf] = diff.lambertian_.sample_f(intersection, wo);

	const float ndotwi = glm::dot(intersection.normal, wi);
	const Ray reflected(intersection.hit_point, wi);

	return color * world.trace_ray(reflected, depth - 1) * ndotwi / pdf;
}

ColorVec Diffuse::shade(const World& world, const Ray& ray, const intersectionRec& intersection, int32_t depth) const
{
	ColorVec res;
	if(true)
	{
		res=new_shading(*this, world, ray, intersection, depth);
	}else
	{
		res=oldshading(*this, world, ray, intersection, depth);
	}
	return res;
}


/*
ColorVec Diffuse::shade(const World& world, const Ray& ray, const intersectionRec& intersectionRec, const int32_t depth) const
{
	const auto& intensity_at_point = world.getAmbientLight().intensityAtPoint(intersectionRec.hit_point);
	const auto& ambient_intensity = intensity_at_point * (color_);
	const auto& out = scatter(ray, intersectionRec);

	if (out.has_value())
	{
		const Ray result = out.value();
		auto out=world.trace_ray(result, depth - 1);
		out.clamp_to_x_if_bigger_than(3,2);
		return ambient_intensity + 0.5f * out * color_;
	}
	return ambient_intensity;
}
*/
/*
ColorVec Diffuse::shade(const World& world, const Ray& ray, const intersectionRec& intersectionRec, int32_t depth) const
{
	const Vector3 wo = -ray.direction;
	const auto [color, wi, pdf] =lambertian_.sample_f(intersectionRec, wo);

	const float ndotwi = glm::dot(intersectionRec.normal, wi);
	const Ray reflected(intersectionRec.hit_point, wi);

	return color * world.trace_ray(reflected, depth - 1) * ndotwi / pdf;

}
*/