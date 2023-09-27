//
// Created by Misael on 23/06/2023.
//

#include "Dielectric.h"

#include <cmath>
#include "../World.h"

ColorVec
Dielectric::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    ColorVec L = Phong::shade(world, ray, intersection, depth);
    Vector3 wo(-ray.direction);
    const auto [fr, wi, pdf] = fresnel_brdf.sample_f(intersection, wo);
    Ray reflected_ray(intersection.hit_point, wi);
    float t = FLT_MAX;
    ColorVec Lr, Lt;
    const float ndotwi = dot(intersection.normal, wi);
    if (fresnel_btdf.internal_reflection(ray.direction, intersection) < 0.0f) {
        if (ndotwi < .0f) {
            Lr = world.trace_ray(reflected_ray, t, depth - 1);
            L += cf_in.powc(t) * Lr;
        } else {
            Lr = world.trace_ray(reflected_ray, t, depth - 1);
            L += cf_out.powc(t) * Lr;
        }
    } else {
        const auto [ft, wt, pdf] = fresnel_btdf.sample_f(intersection, wo);
        Ray transmitted_ray(intersection.hit_point, wt);
        float ndotwt = dot(intersection.normal, wt);
        if (ndotwi < 0.0) {
// reflected ray is inside
            Lr = fr * world.trace_ray(reflected_ray, t,
                                      depth - 1) * std::fabs(ndotwi);
            L += cf_in.powc(t) * Lr; // inside filter color
// transmitted ray is outside
            Lt = ft * world.trace_ray(transmitted_ray, t, depth - 1);
            L += cf_out.powc(t) * Lt; // outside filter color
        } else {
            Lr = fr * world.trace_ray(reflected_ray, t,
                                                 depth - 1) * std::fabs(ndotwi);
            L += cf_out.powc(t) * Lr;

            Lt = ft * world.trace_ray(transmitted_ray, t,
                                                depth-1) * std::fabs(ndotwt);
            L += cf_in.powc(t) * Lt;
        }
    }
    return L;
}
