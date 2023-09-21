//
// Created by Misael on 19/09/2023.
//

#ifndef OCTREE_MODEL_PRIMITIVE_H
#define OCTREE_MODEL_PRIMITIVE_H


#include "../octree/octree.h"

class Primitive {
    virtual octree::NodeType classify() = 0;
};


#endif //OCTREE_MODEL_PRIMITIVE_H
