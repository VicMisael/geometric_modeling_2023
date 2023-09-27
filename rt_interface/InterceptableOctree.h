//
// Created by Misael on 26/09/2023.
//

#ifndef OCTREE_MODEL_INTERCEPTABLEOCTREE_H
#define OCTREE_MODEL_INTERCEPTABLEOCTREE_H


#include "../strippedRayTracer/RayTracerRedone/tracer/objects/VirtualObject.h"
#include "../octree/octree.h"

class InterceptableOctree : public VirtualObject {
    const std::shared_ptr<octree::Octree> octree;
private:
    [[nodiscard]] std::optional<intersectionRec>  checkNodeIntersection(const Ray &ray, const std::shared_ptr<octree::Node> node) const;
public:
    explicit InterceptableOctree(const std::shared_ptr<octree::Octree>& octree, const std::shared_ptr<Material> &material);

    [[nodiscard]] std::optional<intersectionRec> intersects(const Ray &ray) const override;

    void transform(Matrix4x4 m) override;

    [[nodiscard]] std::shared_ptr<AABB> bounding_box() const override;

    [[nodiscard]] std::tuple<Point3, Vector3> pointAtSurface() const override;

    [[nodiscard]] float getArea() const override;

    [[nodiscard]] float getPdf() const override;

    [[nodiscard]] bool hasBoundingBox() const override;

};


#endif //OCTREE_MODEL_INTERCEPTABLEOCTREE_H
