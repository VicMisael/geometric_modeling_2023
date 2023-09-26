//
// Created by misae on 21/09/2023.
//

#include "Box.h"

bool Box::isInsideBoundingBox(glm::vec3 point) const  {
    return (point.x >= min_point.x && point.x <= max_point.x) &&
           (point.y >= min_point.y && point.y <= max_point.y) &&
           (point.z >= min_point.z && point.z <= max_point.z);
}

octree::NodeType Box::classify(BoundingBox boundingBox) const {
    const auto vertexes = boundingBox.generateCubeVertices();
    int insideCount = 0;
    for (const auto vertex: vertexes) {
        insideCount += isInsideBoundingBox(vertex);
    }
    if (insideCount == 8) return octree::BLACK;
    if (insideCount > 0) return octree::GRAY;
    return octree::WHITE;
}

BoundingBox Box::cubedBoundingBox() const
{
    //return { this->min_point,this->max_point };
    return BoundingBox::GenerateCubedBoundingBox(this->min_point, this->max_point);
}

void Box::transform(glm::mat4x4 matrix) {
    min_point = matrix * glm::vec4(min_point, 1);
    max_point = matrix * glm::vec4(max_point, 1);
}
