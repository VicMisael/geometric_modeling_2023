#include "PointLight.h"
#include "../Ray.h"
#include "../World.h"
#include "../../utils/utility.h"

#include <glm/geometric.hpp>


float length(const Vector3 a) {
    return glm::length(a);
}

ColorVec PointLight::intensityAtPoint(const Point3 p) const {
    using namespace utility;
    return inversesqrt(length(getVector(p))) * intensity * color;
}

Vector3 PointLight::getVector(const Point3 p) const {
    return point - p;
}

Vector3 PointLight::getVectorNormalized(const Point3 p) const {
    return normalize(PointLight::getVector(p));
}

bool PointLight::shadow_hit(const World &world, const Ray &outgoing) const {

    const float distance = length(outgoing.origin - this->point);
    const std::optional<intersectionRec> intersection = world.hit(outgoing);
    if (intersection) {
        const auto &intersection_data = intersection.value();
        if (intersection_data.material->castShadow() && intersection_data.tmin > 0.01f && intersection_data.tmin <= distance) {
            return true;
        }
    }

    return false;

}

