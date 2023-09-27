//
// Created by Misael on 03/06/2023.
//

#include "TexturedPhongReflective.h"
#include <glm/geometric.hpp>
#include "../World.h"

ColorVec TexturedPhongReflective::shade(const World &world, const Ray &ray, const intersectionRec &intersection,
                                        int32_t depth) const {
    ColorVec L = texture_->value(intersection.u,intersection.v,intersection.hit_point)*Phong::shade(world, ray, intersection, depth);
    const auto wo = -ray.direction;
    const auto [color,wi,pdf] = reflective_brdf.sample_f(intersection, wo);
    const Ray reflected(intersection.hit_point, wi);
    L += color*world.trace_ray(reflected, depth - 1) * dot(intersection.normal, wi) / pdf;
    return L;
}
