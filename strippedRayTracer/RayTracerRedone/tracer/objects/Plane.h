#pragma once

#include "VirtualObject.h"
#include "glm/geometric.hpp"

class Plane : public VirtualObject {
public:
    Point3 point;
    Vector3 normal;

    Plane(Point3 _point, Vector3 _normal, std::shared_ptr<Material> _material) : VirtualObject(_material),
                                                                                 point(_point),
                                                                                 normal(normalize(_normal)) {};

    std::optional<intersectionRec> intersects(const Ray &ray) const override;

    bool hasBoundingBox() const override  {
        return false;
    }

    void transform(Matrix4x4 m) override;

    float getArea() const override ;

    std::tuple<Point3, Vector3> pointAtSurface() const override;


};

