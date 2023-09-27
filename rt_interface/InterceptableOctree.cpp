//
// Created by Misael on 26/09/2023.
//

#include "InterceptableOctree.h"
#include "IntersectionTests.h"

std::optional<intersectionRec>
InterceptableOctree::checkNodeIntersection(const Ray &ray, const std::shared_ptr<octree::Node> node) const {
    switch (node->nodeType) {

        case octree::BLACK:
            if (RTUtils::checkIntersection(ray))
                return RTUtils::processBoundingBoxIntersection(ray, node->boundingBox.min, node->boundingBox.max,
                                                               this->material);
            break;
        case octree::GRAY: {
            if (RTUtils::checkIntersection(ray)) {

            }
        }
            break;
        case octree::WHITE:
            return {};
            break;
    }
};

std::optional<intersectionRec> InterceptableOctree::intersects(const Ray &ray) const {
    return checkNodeIntersection(ray, octree->rootNode);
}


void InterceptableOctree::transform(Matrix4x4 m) {
    VirtualObject::transform(m);
}

std::shared_ptr<AABB> InterceptableOctree::bounding_box() const {
    return VirtualObject::bounding_box();
}

std::tuple<Point3, Vector3> InterceptableOctree::pointAtSurface() const {
    return VirtualObject::pointAtSurface();
}

float InterceptableOctree::getArea() const {
    return 0;
}

float InterceptableOctree::getPdf() const {
    return VirtualObject::getPdf();
}

bool InterceptableOctree::hasBoundingBox() const {
    return true;
}

InterceptableOctree::InterceptableOctree(const std::shared_ptr<octree::Octree> &_octree,
                                         const std::shared_ptr<Material> &material) : octree(_octree),
                                                                                      VirtualObject(material) {

}

