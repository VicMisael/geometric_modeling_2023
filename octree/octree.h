//
// Created by Misael on 08/09/2023.
//

#ifndef OCTREE_MODEL_OCTREE_H
#define OCTREE_MODEL_OCTREE_H


#include <memory>
#include "../primitives/Primitive.h"

namespace octree {
    enum NodeType {
        BLACK,
        GRAY,
        WHITE
    };

    class Node {
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> children[8];
        std::shared_ptr<Node> bounds[8];
        bool hasChildren;
        NodeType nodeType;
        NodeType classify(Primitive primitive);

    };

    class Octree {
        std::shared_ptr<Node> rootNode;
        int maxDepth;

    private:
        Octree(Node rootNode) {}
    };

}

#endif //OCTREE_MODEL_OCTREE_H
