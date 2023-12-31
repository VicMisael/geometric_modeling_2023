//
// Created by misae on 21/09/2023.
//

#include "Sphere.h"

BoundingBox Sphere::cubedBoundingBox() const {

//    return {center - glm::vec3( radius),
//            center + glm::vec3( radius)};

    return BoundingBox::GenerateCubedBoundingBox(center - glm::vec3(radius), center + glm::vec3(radius));
}

void Sphere::transform(glm::mat4x4 matrix) {
    center = matrix * glm::vec4(center, 1);
}

octree::NodeType Sphere::classify(BoundingBox boundingBox) const {


    auto vertexes = boundingBox.generateCubeVertices();
    int cornersInsideCount = 0;
    for (const auto &vertice: vertexes) {
        if (length(vertice - center) <= radius) {
            cornersInsideCount++;
        }
    }
    if (cornersInsideCount == 8) return octree::BLACK;
    if (cornersInsideCount > 0) return octree::GRAY;
    return octree::WHITE;

}

std::string Sphere::name() {
    return "Sphere";
}
