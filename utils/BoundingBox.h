//
// Created by Misael on 24/09/2023.
//

#ifndef OCTREE_MODEL_BOUNDINGBOX_H
#define OCTREE_MODEL_BOUNDINGBOX_H

#include <glm/vec3.hpp>
#include <vector>

class BoundingBox {
public:
    glm::vec3 min;
    glm::vec3 max;

    BoundingBox(glm::vec3 min, glm::vec3 max) : min(min), max(max) {}

    static BoundingBox GenerateCubedBoundingBox(glm::vec3 min, glm::vec3 max);

    [[nodiscard]] glm::vec3 center() const {
        return (min + max) * 0.5f;
    }

    [[nodiscard]] glm::vec3 halfDimensions() const {
        return (max - min) * 0.5f;
    }

    float volume();

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


#endif //OCTREE_MODEL_BOUNDINGBOX_H
