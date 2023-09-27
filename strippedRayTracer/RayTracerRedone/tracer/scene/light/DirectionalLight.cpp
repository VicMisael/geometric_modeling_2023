#include "DirectionalLight.h"

#include <glm/geometric.hpp>

#include "../Ray.h"
#include "../World.h"

Vector3 DirectionalLight::getVector(const Point3 p) const {
    return direction_;
}

Vector3 DirectionalLight::getVectorNormalized(const Point3 p) const {
    return glm::normalize(getVector(p));
}

ColorVec DirectionalLight::intensityAtPoint(const Point3) const {
    return this->intensity * this->color;
}

bool DirectionalLight::shadow_hit(const World &world, const Ray &outgoing) const {


    const std::optional<intersectionRec> intersection = world.hit(outgoing);
    if (intersection.has_value()) {
        const auto &intersection_data = intersection.value();
        if (intersection_data.material->castShadow() && intersection_data.tmin > 0.01f) {
            return true;
        }
    }

    return false;
}
