//
// Created by Misael on 08/09/2023.
//

#include "octree.h"

#include <string>
#include <glm/geometric.hpp>
#include <utility>


void octree::Node::subdivide() {
    glm::vec3 mid = this->boundingBox.center();
    children[0] = std::make_unique<Node>(BoundingBox(boundingBox.min, mid)); // Bottom-front-left
    children[1] = std::make_unique<Node>(BoundingBox(glm::vec3(mid.x, boundingBox.min.y, boundingBox.min.z),
                                                     glm::vec3(boundingBox.max.x, mid.y, mid.z))); // Bottom-front-right
    children[2] = std::make_unique<Node>(BoundingBox(glm::vec3(boundingBox.min.x, boundingBox.min.y, mid.z),
                                                     glm::vec3(mid.x, mid.y, boundingBox.max.z))); // Bottom-back-left
    children[3] = std::make_unique<Node>(BoundingBox(glm::vec3(mid.x, boundingBox.min.y, mid.z),
                                                     glm::vec3(boundingBox.max.x, mid.y,
                                                               boundingBox.max.z))); // Bottom-back-right
    children[4] = std::make_unique<Node>(BoundingBox(glm::vec3(boundingBox.min.x, mid.y, boundingBox.min.z),
                                                     glm::vec3(mid.x, boundingBox.max.y, mid.z))); // Top-front-left
    children[5] = std::make_unique<Node>(BoundingBox(glm::vec3(mid.x, mid.y, boundingBox.min.z),
                                                     glm::vec3(boundingBox.max.x, boundingBox.max.y,
                                                               mid.z))); // Top-front-right
    children[6] = std::make_unique<Node>(BoundingBox(glm::vec3(boundingBox.min.x, mid.y, mid.z),
                                                     glm::vec3(mid.x, boundingBox.max.y,
                                                               boundingBox.max.z))); // Top-back-left
    children[7] = std::make_unique<Node>(
            BoundingBox(glm::vec3(mid.x, mid.y, mid.z), boundingBox.max)); // Top-back-right
}

void
octree::Node::makeTree(const std::shared_ptr<Primitive> &_primitive, int _depth) {
    nodeType = _primitive->classify(boundingBox);
    if (nodeType == GRAY && _depth > 0) {
        this->subdivide();
        for (auto &child: children) {
            child->makeTree(_primitive, _depth - 1);
        }
    }
}

std::string octree::Node::parse() {
    switch (nodeType) {
        case BLACK:
            return "B";
        case GRAY: {
            std::string start = "(";
            for (auto &child: children) {
                start += child->parse();
            }
            return start;
        }
        case WHITE:
            return "W";
    }
}

void octree::Node::makeTreeInit(const std::shared_ptr<Primitive> &_primitive, int _depth) {

    nodeType = GRAY;
    if (_depth > 0) {
        this->subdivide();
        for (auto &child: children) {
            child->makeTree(_primitive, _depth - 1);
        }
    }

}

octree::Octree::Octree(const std::shared_ptr<Primitive> &primitive, int depth) : rootNode(
        std::make_shared<Node>(primitive->minMax())) {
    rootNode->makeTreeInit(primitive, depth);
}

std::string octree::Octree::parse() {
    return this->rootNode->parse();
}
