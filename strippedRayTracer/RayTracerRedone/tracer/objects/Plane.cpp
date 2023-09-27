#include "Plane.h"
#include <glm/geometric.hpp>
#include "../utils/utility.h"
#include "../utils/OrthonormalBase.h"


glm::vec3 computeU(glm::vec3 normal) {
    glm::vec3 randomVec = glm::vec3(1, 0, 0);
    if (glm::dot(normal, randomVec) > 0.99) // they are too parallel
        randomVec = glm::vec3(0, 1, 0);

    return glm::normalize(glm::cross(normal, randomVec));
}

glm::vec3 computeV(glm::vec3 normal, glm::vec3 u) {
    return glm::cross(normal, u);
}

std::tuple<float, float> computeUV(glm::vec3 pointInPlane, glm::vec3 otherPoint, glm::vec3 normal) {
    glm::vec3 u = computeU(normal);
    glm::vec3 v = computeV(normal, u);

    glm::vec3 delta = otherPoint - pointInPlane;

    float uCoordinate = glm::dot(delta, u);
    float vCoordinate = glm::dot(delta, v);

    return {glm::mod(uCoordinate / 100,1.0f), glm::mod(vCoordinate / 100,1.0f)};
}

std::optional<intersectionRec> Plane::intersects(const Ray &ray) const {
    using namespace glm;
    const float dot_dir_normal = dot(ray.direction, normal);
    const float t = dot(point - ray.origin, normal) / dot_dir_normal;
    if (t > Constants::EPSILON) {
        const auto intersectionPoint = ray.point_at(t);
        const auto [u, v] = computeUV(point, intersectionPoint, normal);
        return intersectionRec{t, ray.point_at(t), normal, material, u, v};
    }

    return {};
}

void Plane::transform(Matrix4x4 m) {
    point = Vector3(m * Vector4(point, 1));
    normal = Vector3(m * Vector4(normal, 0));
}

float Plane::getArea() const {
    return INFINITY;
}

std::tuple<Point3, Vector3> Plane::pointAtSurface() const {
    const OrthonormalBase uvw(this->normal);
    return {this->point + utility::random(FLT_MIN, FLT_MAX) * (uvw.u() + uvw.v()), normal};

}
