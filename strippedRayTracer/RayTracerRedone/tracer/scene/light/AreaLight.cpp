//
// Created by Misael on 04/07/2023.
//

#include <glm/gtx/norm.hpp>
#include "AreaLight.h"
#include "../World.h"
#include "../materials/DiffuseLight.h"

ColorVec AreaLight::intensityAtPoint(const Point3 p, const AreaLight::AreaLightState& areaLightState) const
{
	const auto ndotd = dot(-areaLightState.normal_at_point, areaLightState.wi);

	auto c = dynamic_cast<DiffuseLight*>(object->material.get());

	if (ndotd > 0.0)
		return c->getL();
	else
		return ColorVec();
}

float AreaLight::G(const Point3 hitpoint, const AreaLight::AreaLightState& areaLightState) const
{
	const auto ndotd = dot(-areaLightState.normal_at_point, areaLightState.wi);
	const auto d2 = glm::length2(hitpoint - areaLightState.sample_point);
	return (ndotd / d2);
}

bool AreaLight::shadow_hit(const World& world, const Ray& outgoing, const AreaLight::AreaLightState&) const
{
	const std::optional<intersectionRec> intersection = world.hit(outgoing);
	if (intersection.has_value())
	{
		const auto& intersection_data = intersection.value();
		if (intersection_data.material->castShadow() && intersection_data.tmin > 0.001f)
		{
			return true;
		}
	}

	return false;
}


float AreaLight::pdf() const
{
	return object->getPdf();
}

AreaLight::AreaLightState AreaLight::generateState(Point3 p) const
{
	const auto [point, normal] = object->pointAtSurface();
	Vector3 wi = point - p;
	return {point, normal, wi};
}

AreaLight::AreaLight(const std::shared_ptr<VirtualObject>& object)
	: Light(0.0, ColorVec()), object(object)
{
	const auto material = object->material;
	if (typeid(*material) != typeid(DiffuseLight))
	{
		throw std::invalid_argument("Material of the Object should be a DiffuseLight");
	}
}

Vector3 AreaLight::getVectorNormalized(AreaLight::AreaLightState areaLightState) const
{
	return glm::normalize(areaLightState.wi);
}
