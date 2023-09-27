//
// Created by Misael on 21/06/2023.
//

#pragma once

#include "VirtualObject.h"

class Disk : public VirtualObject {
    Point3 center = Point3(0.0f);
    Vector3 normal = Vector3(0.0f, 1.0f, 0.0f);
    float r_squared = 1.0f;
    std::tuple<float, float> getUVMapping(const Point3 point) const;
public:
    explicit Disk( const Point3 &center, const Vector3 &normal, float r,const std::shared_ptr<Material> &material)
            : VirtualObject(material), center(center), normal(normal), r_squared(r * r) {}

    explicit Disk(const std::shared_ptr<Material> &material) : VirtualObject(material) {}

    std::optional<intersectionRec> intersects(const Ray &ray) const override;

    void transform(Matrix4x4 m) override;

    std::shared_ptr<AABB> bounding_box() const override;

    bool hasBoundingBox() const override;

    float getArea() const override;

    [[nodiscard]] std::tuple<Point3, Vector3> pointAtSurface() const override;


};

