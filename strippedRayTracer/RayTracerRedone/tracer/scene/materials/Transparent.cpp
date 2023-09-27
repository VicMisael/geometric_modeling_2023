//
// Created by Misael on 16/06/2023.
//

#include "Transparent.h"
#include "../World.h"

ColorVec
Transparent::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    ColorVec L = Phong::shade(world, ray, intersection, depth);
    Vector3 wo = -ray.direction;
    const auto [colorfr, wi, pdf] = reflective_brdf.sample_f(intersection, wo);
    Ray reflect_ray(intersection.hit_point, wi);
    if (specular_btdf.internal_reflection(ray.direction, intersection) < 0.0f) {
        L += world.trace_ray(reflect_ray, depth - 1);
    } else {
        const auto [color, wt, pdf] = specular_btdf.sample_f(intersection, wo);
        Ray transmitted_ray(intersection.hit_point, wt);
        L += colorfr * world.trace_ray(reflect_ray, depth - 1) * static_cast<float>(fabs(dot(intersection.normal, wi)));
        L += color * world.trace_ray(transmitted_ray, depth - 1) *
             static_cast<float>(fabs(dot(intersection.normal, wt)));
    }
    return L;
}
