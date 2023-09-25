//
// Created by Misael on 19/09/2023.
//

#pragma once

#ifndef OCTREE_MODEL_PRIMITIVE_H
#define OCTREE_MODEL_PRIMITIVE_H

#include <tuple>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../utils/BoundingBox.h"

namespace octree {
    enum NodeType {
        BLACK,
        GRAY,
        WHITE
    };
}
class Primitive {
public:
    virtual octree::NodeType classify(BoundingBox boundingBox) = 0;

    virtual BoundingBox minMax() = 0;

    virtual void transform(glm::mat4x4 matrix) = 0;
};


#endif //OCTREE_MODEL_PRIMITIVE_H
