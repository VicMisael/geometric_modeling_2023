#pragma once

#include "VirtualObject.h"

class Ball : public VirtualObject {
    std::shared_ptr<AABB> aabb;
public:
    Point3 center;
    float radius;

    Ball(Point3 _center, float _radius, std::shared_ptr<Material> _material) : VirtualObject(_material),
                                                                               center(_center), radius(_radius) {
        aabb = std::make_shared<AABB>(AABB(
                center - Vector3(radius, radius, radius),
                center + Vector3(radius, radius, radius)));
    };

    Ball(Point3 _center, float _radius) : VirtualObject(), center(_center), radius(_radius) {
        aabb = std::make_shared<AABB>(AABB(
                center - Vector3(radius, radius, radius),
                center + Vector3(radius, radius, radius)));
    };

    [[nodiscard]] std::optional<intersectionRec> intersects(const Ray &ray) const override;

    [[nodiscard]] std::shared_ptr<AABB> bounding_box() const override;

    void transform(Matrix4x4 m) override;

    float getArea() const override;

    std::tuple<Point3, Vector3> pointAtSurface() const override;

protected:
    void calculateBoundingBox();

};

