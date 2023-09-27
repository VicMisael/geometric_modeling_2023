#include "Ball.h"
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/exponential.hpp>
#include "../scene/World.h"
#include "../utils/utility.h"

std::tuple<float, float> get_sphere_uv(const Point3 p) {
    // p: a given point on the sphere of radius one, centered at the origin.
    // u: returned value [0,1] of angle around the Y axis from X=-1.
    // v: returned value [0,1] of angle from Y=-1 to Y=+1.
    //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
    //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
    //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

    using namespace Constants;
    constexpr auto f_pi = static_cast<float>(pi);
    const float theta = glm::acos(-p.y);
    const float phi = atan2f(-p.z, p.x) + f_pi;

    const float u = phi / (2 * pi);
    const float v = theta / pi;
    return {u, v};
}

std::optional<intersectionRec> Ball::intersects(const Ray &ray) const {
    if (!aabb->intersects(ray)) {
        return {};
    }
    const Vector3 ray_direction = ray.direction;
    const float &radius = this->radius;
    const Point3 &center = this->center;
    using namespace utility;
    const Vector3 origin_minus_center = ray.origin - center;
    const float a = glm::dot(ray_direction, ray_direction);
    const float b = 2.0f * glm::dot(origin_minus_center, ray_direction);
    const float c = glm::dot(origin_minus_center, origin_minus_center) - radius * radius;
    const float disc = b * b - 4.0f * a * c;
    if (disc < 0.0f) {
        return {};
    }
    const float t1 = (-b + sqrtf(disc)) / (2.0f * a);
    const float t2 = (-b - sqrtf(disc)) / (2.0f * a);
    const float closest = std::min(t1, t2);
    const Vector3 closestPoint = (ray.point_at(closest));
    const Vector3 normal = normalize(closestPoint - center);
    //const Vector3 normal= (origin_minus_center + closest * ray_direction) / radius;
    const auto [u, v] = get_sphere_uv(normal);
    return intersectionRec{closest, closestPoint, normal, material, u, v};
}

std::shared_ptr<AABB> Ball::bounding_box() const {
    return aabb;
}

void Ball::transform(Matrix4x4 m) {
    center = Vector3(m * Vector4(center, 1));
    calculateBoundingBox();
}


void Ball::calculateBoundingBox() {
    this->aabb = std::make_shared<AABB>(AABB(
            center - Vector3(radius, radius, radius),
            center + Vector3(radius, radius, radius)));
}

float Ball::getArea() const {
    return 4.0f * static_cast<float>(Constants::pi) * radius * radius;
}

std::tuple<Point3, Vector3> Ball::pointAtSurface() const {
    float theta = 2.0f * glm::pi<float>() * utility::random_in_interval(0, 1); // azimuthal angle
    float phi = acos(2.0f * utility::random_in_interval(0, 1) - 1.0f); // polar angle

    const float x = center.x + radius * sin(phi) * cos(theta);
    const float y = center.y + radius * sin(phi) * sin(theta);
    const float z = center.z + radius * cos(phi);
    const Point3 point(x, y, z);
    const Vector3 normal = normalize(point - center);
    return {point, normal};
}
