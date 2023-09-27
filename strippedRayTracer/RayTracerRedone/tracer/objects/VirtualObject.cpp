//
// Created by misae on 31/05/2023.
//
#include <optional>
#include "VirtualObject.h"
#include "BoundingBox/AABB.h"

#include "../scene/World.h"
#include "../utils/utility.h"


class internal : public Material {
public:
    internal() = default;

    [[nodiscard]] ColorVec
    shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override {
        const auto &hitPoint = intersection.hit_point;
        const Ray reflected(hitPoint, utility::reflect_vector(normalize(ray.direction), intersection.normal));
        return 0.5f * world.trace_ray(reflected, depth-(depth-1));
    }
} t;

std::shared_ptr<AABB> VirtualObject::bounding_box() const {
    return {};
}

VirtualObject::VirtualObject() {
    material = std::move(std::make_shared<internal>(t));
}
