//
// Created by Misael on 08/09/2023.
//

#ifndef OCTREE_MODEL_OCTREE_H
#define OCTREE_MODEL_OCTREE_H


#include <memory>
#include <glm/vec3.hpp>

#include "../primitives/Primitive.h"

namespace octree {

    class Node {
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> children[8];
        glm::vec3 minBound;
        glm::vec3 maxBound;
        bool hasChildren;
        NodeType nodeType;
        float edgeLength;
        int height;
    };

    class Octree {
        std::shared_ptr<Node> rootNode;
        int maxDepth;
        glm::vec3 min;
        glm::vec3 max;

    private:
        explicit Octree(Node rootNode);

    public:
        Octree Build(const std::shared_ptr<Primitive>& primitive, int depth);
    };

}

#endif //OCTREE_MODEL_OCTREE_H
/*
 * void subdivide() {
    glm::vec3 mid = (bounds.min + bounds.max) * 0.5f;

    // Define the 8 octants
    children[0] = std::make_unique<Octree>(BoundingBox(bounds.min, mid), depth + 1); // Bottom-front-left
    children[1] = std::make_unique<Octree>(BoundingBox(glm::vec3(mid.x, bounds.min.y, bounds.min.z), glm::vec3(bounds.max.x, mid.y, mid.z)), depth + 1); // Bottom-front-right
    children[2] = std::make_unique<Octree>(BoundingBox(glm::vec3(bounds.min.x, bounds.min.y, mid.z), glm::vec3(mid.x, mid.y, bounds.max.z)), depth + 1); // Bottom-back-left
    children[3] = std::make_unique<Octree>(BoundingBox(glm::vec3(mid.x, bounds.min.y, mid.z), glm::vec3(bounds.max.x, mid.y, bounds.max.z)), depth + 1); // Bottom-back-right
    children[4] = std::make_unique<Octree>(BoundingBox(glm::vec3(bounds.min.x, mid.y, bounds.min.z), glm::vec3(mid.x, bounds.max.y, mid.z)), depth + 1); // Top-front-left
    children[5] = std::make_unique<Octree>(BoundingBox(glm::vec3(mid.x, mid.y, bounds.min.z), glm::vec3(bounds.max.x, bounds.max.y, mid.z)), depth + 1); // Top-front-right
    children[6] = std::make_unique<Octree>(BoundingBox(glm::vec3(bounds.min.x, mid.y, mid.z), glm::vec3(mid.x, bounds.max.y, bounds.max.z)), depth + 1); // Top-back-left
    children[7] = std::make_unique<Octree>(BoundingBox(glm::vec3(mid.x, mid.y, mid.z), bounds.max), depth + 1); // Top-back-right
}
*/