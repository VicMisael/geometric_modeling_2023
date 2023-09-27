//
// Created by Misael on 15/06/2023.
//

#include "SampleDielectric.h"
#include "../World.h"
#include "../../utils/utility.h"

ColorVec
SampleDielectric::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    auto material = intersection.material;
    bool front_face = dot(ray.direction, intersection.normal) < 0;
    auto normal = intersection.normal;
    if (!front_face) {
        normal = -normal;
    }

    const float refraction_ratio = front_face ? (1.0 / _reflectance) : _reflectance;
    const Vector3 unit_dir = normalize(ray.direction);
    const float cos_theta = fmin(dot(-unit_dir, normal), 1.0);
    const double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vector3 direction;
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > utility::random_double())
        direction = reflect(unit_dir, normal);
    else
        direction = refract(unit_dir, normal, refraction_ratio);

    return world.trace_ray(Ray(intersection.hit_point, direction), depth - 1);
}
