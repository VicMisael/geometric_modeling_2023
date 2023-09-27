#include "Matte.h"

#include <glm/geometric.hpp>

#include "../World.h"

ColorVec Matte::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    const Vector3 wo = -ray.direction;
    const auto al = world.getAmbientLight();
    ColorVec L = brdf_.rho(wo) * al.intensityAtPoint(intersection.hit_point) * al.getColor();
    for (const auto &light: world.lights()) {
        const auto wi = light->getVectorNormalized(intersection.hit_point);
        const float ndotwi = dot(intersection.normal, wi);
        if (ndotwi > 0) {
            bool in_shadow = false;

            if (intersection.material->castShadow() &&  light->casts_shadow())
                in_shadow =
                            light->shadow_hit(world, Ray(intersection.hit_point, normalize(wi)));

            if (!in_shadow) {
                const auto intensity = light->intensityAtPoint(intersection.hit_point);

                L += brdf_.f(intersection, wo, wi) * intensity * ndotwi;
            }

        }
    }

    for (const auto &light: world.areaLights()) {
        const auto state = light->generateState(intersection.hit_point);
        const auto wi = light->getVectorNormalized(state);
        const float ndotwi = dot(intersection.normal, wi);
        if (ndotwi > 0) {
            bool in_shadow = false;

            if (light->casts_shadow())
                in_shadow =
                          light->shadow_hit(world, Ray(intersection.hit_point, normalize(wi)), state);

            if (!in_shadow) {
                const auto intensity = light->intensityAtPoint(intersection.hit_point, state)
                                       * light->G(intersection.hit_point, state);
//                const auto intensity =
//                        world.trace_ray(Ray(intersection.hit_point, wi),depth-1) * light->G(intersection.hit_point, state);
                L += brdf_.f(intersection, wo, wi) * intensity * ndotwi / light->pdf();
            }
        }
    }

    const auto [color, wi_2, pdf] = brdf_.sample_f(intersection, wo);
    const float ndotwi2 = glm::dot(intersection.normal, wi_2);
    const Ray reflected(intersection.hit_point, wi_2);

    L += color * world.trace_ray(reflected, depth - 1) * ndotwi2 / pdf;

    return L;
}
