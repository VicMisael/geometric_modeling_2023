//
// Created by Misael on 26/09/2023.
//

#include "InterceptableOctree.h"
#include "IntersectionTests.h"


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

std::optional<intersectionRec>
InterceptableOctree::checkNodeIntersection(const Ray &ray, const std::shared_ptr<octree::Node> node) const {
    const auto result = treeIntersects(ray, node);
    if (result.has_value()) {
        const auto resultVal = result.value();
        return intersectionRec{resultVal.tmin, resultVal.point, resultVal.normal, this->material, resultVal.u,
                               resultVal.v};
    }
    return {};
}

std::optional<RTUtils::rt_output>
InterceptableOctree::treeIntersects(const Ray &ray, const std::shared_ptr<octree::Node> node) const {
    float t_min = std::numeric_limits<float>::max();
    if (RTUtils::intersects(ray, node->boundingBox.min, node->boundingBox.max)) {
        RTUtils::rt_output output{};
        for (const auto &child: node->children) {
            const auto min = child->boundingBox.min;
            const auto max = child->boundingBox.max;
            if (RTUtils::intersects(ray, min, max)) {
                switch (child->nodeType) {
                    case octree::BLACK: {
                        const auto result = RTUtils::processBoundingBoxIntersection(ray, min, max);
                        if (result.has_value() && result.value().tmin < t_min) {
                            output = result.value();
                            t_min = output.tmin;
                        }
                    }
                        break;
                    case octree::GRAY: {
                        const auto result = treeIntersects(ray, child);
                        if (result.has_value() && result.value().isset && result.value().tmin < t_min) {
                            const auto res = result.value();
                            output = result.value();
                            t_min = output.tmin;
                        }
                    }
                        break;
                    default://ignore
                        break;
                }
            }

        }

        return output;
    }
    return {};
}
