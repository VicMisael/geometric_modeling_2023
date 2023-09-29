//
// Created by Misael on 08/09/2023.
//

#include "octree.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>


void octree::Node::subdivide() {
    hasChildren = true;
    const glm::vec3 mid = this->boundingBox.center();
    children[0] = std::make_shared<Node>(BoundingBox(boundingBox.min, mid)); // Bottom-front-left
    children[1] = std::make_shared<Node>(BoundingBox(glm::vec3(mid.x, boundingBox.min.y, boundingBox.min.z),
                                                     glm::vec3(boundingBox.max.x, mid.y, mid.z))); // Bottom-front-right
    children[2] = std::make_shared<Node>(BoundingBox(glm::vec3(boundingBox.min.x, boundingBox.min.y, mid.z),
                                                     glm::vec3(mid.x, mid.y, boundingBox.max.z))); // Bottom-back-left
    children[3] = std::make_shared<Node>(BoundingBox(glm::vec3(mid.x, boundingBox.min.y, mid.z),
                                                     glm::vec3(boundingBox.max.x, mid.y,
                                                               boundingBox.max.z))); // Bottom-back-right
    children[4] = std::make_shared<Node>(BoundingBox(glm::vec3(boundingBox.min.x, mid.y, boundingBox.min.z),
                                                     glm::vec3(mid.x, boundingBox.max.y, mid.z))); // Top-front-left
    children[5] = std::make_shared<Node>(BoundingBox(glm::vec3(mid.x, mid.y, boundingBox.min.z),
                                                     glm::vec3(boundingBox.max.x, boundingBox.max.y,
                                                               mid.z))); // Top-front-right
    children[6] = std::make_shared<Node>(BoundingBox(glm::vec3(boundingBox.min.x, mid.y, mid.z),
                                                     glm::vec3(mid.x, boundingBox.max.y,
                                                               boundingBox.max.z))); // Top-back-left
    children[7] = std::make_shared<Node>(
            BoundingBox(glm::vec3(mid.x, mid.y, mid.z), boundingBox.max)); // Top-back-right
}

void
octree::Node::makeTree(const std::shared_ptr<Primitive> &_primitive, int _depth) {
    nodeType = _primitive->classify(boundingBox);
    if (nodeType == GRAY) {
        if (_depth > 0) {
            this->subdivide();
            for (auto &child: children) {
                child->makeTree(_primitive, _depth - 1);
            }
        } else {
            nodeType = BLACK;
        }
    }
}

void octree::Node::makeTreeInit(const std::shared_ptr<Primitive> &_primitive, int _depth) {
    nodeType = GRAY;
    if (_depth > 0) {
        this->subdivide();
        for (auto &child: children) {
            child->makeTree(_primitive, _depth - 1);

        }
    } else {
        nodeType = BLACK;
    }

}

std::string octree::Node::parse() {
    switch (nodeType) {
        case BLACK:
            return "B";
        case GRAY: {
            std::string start = "(";
            if (hasChildren) {
                for (const auto &child: children) {
                    start += child->parse();
                }
            }
            return start;
        }
        case WHITE:
            return "W";
    }
    return "??";
}

float octree::Node::volume() {
    float volume = 0;
    if (hasChildren) {
        for (const auto &child: children) {
            switch (child->nodeType) {

                case BLACK:
                    volume += child->boundingBox.volume();
                    break;
                case GRAY:
                    volume += child->volume();
                    break;
                case WHITE:
                    break;
            }
        }
    }
    return volume;
}

void octree::Node::translate(glm::vec3 point) {
    auto matrix = glm::translate(glm::mat4x4(1.0f), point);
    glm::vec3 min = matrix * glm::vec4(boundingBox.min, 1);
    glm::vec3 max = matrix * glm::vec4(boundingBox.max, 1);
    this->boundingBox.min = min;
    this->boundingBox.max = max;
    if (hasChildren) {
        for (const auto &child: children) {
            child->translate(point);
        }
    }

}

void octree::Node::scale(float size) {
    auto matrix = glm::scale(glm::mat4x4(1.0f), glm::vec3(size));
    this->boundingBox.min = matrix * glm::vec4(this->boundingBox.min, 1);
    this->boundingBox.max = matrix * glm::vec4(this->boundingBox.max, 1);
    if (hasChildren) {
        for (const auto &child: children) {
            child->scale(size);
        }
    }
}


octree::Octree::Octree(const std::shared_ptr<Primitive> &primitive, int depth) : rootNode(
        std::make_shared<Node>(primitive->cubedBoundingBox())) {
    rootNode->makeTreeInit(primitive, depth - 1);
}

std::string octree::Octree::parse() {
    return this->rootNode->parse();
}

float octree::Octree::volume() {
    return rootNode->volume();
}

void octree::Octree::scale(float size) {
    this->rootNode->scale(size);
}

void octree::Octree::translate(glm::vec3 point) {
    this->rootNode->translate(point);
}
