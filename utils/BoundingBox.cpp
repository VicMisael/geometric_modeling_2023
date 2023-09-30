//
// Created by Misael on 24/09/2023.
//

#include <glm/common.hpp>
#include "BoundingBox.h"

BoundingBox BoundingBox::GenerateCubedBoundingBox(glm::vec3 min, glm::vec3 max) {
    // Compute the dimensions of the proposed box
    glm::vec3 dimensions = max - min;

    // Determine the largest dimension
    float maxSize = glm::max(dimensions.x, glm::max(dimensions.y, dimensions.z));

    // Adjust the min and max corners to form a cube
    glm::vec3 minCorner = min;
    glm::vec3 maxCorner = min + glm::vec3(maxSize, maxSize, maxSize);
    return {minCorner, maxCorner};
}

float BoundingBox::volume() const {
    glm::vec3 dimensions = max - min;
    return dimensions.x * dimensions.y * dimensions.z;
}

BoundingBox BoundingBox::GenerateCubeByCenterAndSideLength(glm::vec3 center, float side_length) {
    glm::vec3 min = center - glm::vec3(side_length / 2);
    glm::vec3 max = center + glm::vec3(side_length / 2);
    return {min, max};
}
