//
// Created by Misael on 24/09/2023.
//

#ifndef OCTREE_MODEL_BOUNDINGBOX_H
#define OCTREE_MODEL_BOUNDINGBOX_H

#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <vector>

class BoundingBox {
public:
    glm::vec3 min;
    glm::vec3 max;

    BoundingBox(glm::vec3 min, glm::vec3 max) : min(min), max(max) {}

    static BoundingBox GenerateCubedBoundingBox(glm::vec3 min, glm::vec3 max);

    static BoundingBox GenerateCubeByCenterAndSideLength(glm::vec3 center, float side_length);

    [[nodiscard]] glm::vec3 center() const {
        return (min + max) * 0.5f;
    }

    [[nodiscard]] glm::vec3 halfDimensions() const {
        return (max - min) * 0.5f;
    }

    float volume() const;

    std::vector<glm::vec3> generateCubeVertices() {
        std::vector<glm::vec3> vertices(8);

        vertices[0] = min;
        vertices[1] = glm::vec3(min.x, min.y, max.z);
        vertices[2] = glm::vec3(min.x, max.y, min.z);
        vertices[3] = glm::vec3(min.x, max.y, max.z);
        vertices[4] = glm::vec3(max.x, min.y, min.z);
        vertices[5] = glm::vec3(max.x, min.y, max.z);
        vertices[6] = glm::vec3(max.x, max.y, min.z);
        vertices[7] = max;

        return vertices;
    }
};



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



#endif //OCTREE_MODEL_BOUNDINGBOX_H
