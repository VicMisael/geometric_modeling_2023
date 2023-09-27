//
// Created by Misael on 24/06/2023.
//

#include "DiffuseLight.h"
#include "../../utils/utility.h"
#include "../World.h"

ColorVec
DiffuseLight::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
	return color;
//
//	const auto o_to_hit_point = ray.origin - intersection.hit_point;
//	const auto len = length(o_to_hit_point);
//	return glm::inversesqrt(len) * intensity * color;
    return this->getL();

}

ColorVec DiffuseLight::getL() const {
    return intensity * color;
}

DiffuseLight::DiffuseLight(const ColorVec &color, float intensity) : color(color),
                                                                     intensity(intensity) {
}
