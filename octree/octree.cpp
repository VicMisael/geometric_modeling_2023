//
// Created by Misael on 08/09/2023.
//

#include "octree.h"
#include "iostream"
octree::NodeType octree::Node::classify(Primitive primitive) {
    return octree::BLACK;
}

octree::NodeType octree::Node::classify(std::shared_ptr<Primitive> primitive) {
    return octree::BLACK;
}

octree::Octree octree::Octree::Build(std::shared_ptr<Primitive> primitive) {
    return octree::Octree(octree::Node());
}

octree::Octree::Octree(octree::Node rootNode) {

}
