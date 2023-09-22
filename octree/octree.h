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
        std::shared_ptr<glm::vec3> bounds[8];
        bool hasChildren;
        NodeType nodeType;
        float edgeLength;
    };

    class Octree {
        std::shared_ptr<Node> rootNode;
        int maxDepth;

    private:
        Octree(Node rootNode);
    public:
        Octree Build(std::shared_ptr<Primitive> primitive);
    };

}

#endif //OCTREE_MODEL_OCTREE_H
