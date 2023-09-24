//
// Created by Misael on 08/09/2023.
//

#include "octree.h"
#include <glm/geometric.hpp>

octree::Octree octree::Octree::Build(const std::shared_ptr<Primitive>& primitive, int depth) {
    auto points = primitive->minMax();
    glm::vec3 min=get<0>(points);
    glm::vec3 max=get<1>(points);
    auto distance = glm::length(max-min);

}

octree::Octree::Octree(octree::Node rootNode) {

}
