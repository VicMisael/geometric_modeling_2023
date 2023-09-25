//
// Created by Misael on 08/09/2023.
//
#pragma once
#ifndef OCTREE_MODEL_OCTREE_H
#define OCTREE_MODEL_OCTREE_H


#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <utility>

#include "../primitives/Primitive.h"

namespace octree {

    class Node : std::enable_shared_from_this<Node> {
        std::shared_ptr<Node> children[8];
        BoundingBox boundingBox;
        NodeType nodeType;
        bool hasChildren = false;
    private:
        void subdivide();


    public:
        void makeTree(const std::shared_ptr<Primitive> &_primitive, int _depth);
        void makeTreeInit(const std::shared_ptr<Primitive>& _primitive, int _depth);

        std::string parse();

        explicit Node(BoundingBox box) : boundingBox(std::move(box)) {};

    };

    class Octree {
        std::shared_ptr<Node> rootNode;

    public:
        explicit Octree(const std::shared_ptr<Primitive> &primitive, int depth);

        std::string parse();

    };

}


void octree::Node::subdivide() {
    hasChildren = true;
    glm::vec3 mid = this->boundingBox.center();
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
            for (auto& child : children) {
                child->makeTree(_primitive, _depth - 1);
            }
        }
        else
        {
            nodeType = BLACK;
        }
    }
}

void octree::Node::makeTreeInit(const std::shared_ptr<Primitive>& _primitive, int _depth)
{
    nodeType = GRAY;
    if (_depth > 0) {
        this->subdivide();
        for (auto& child : children) {
            child->makeTree(_primitive, _depth - 1);

        }
    }
    else
    {
        nodeType = BLACK;
    }

}

std::string octree::Node::parse(){
    switch (nodeType) {
        case BLACK:
            return "B";
        case GRAY: {
            std::string start = "(";
            if (hasChildren){
	            for (const auto &child: children) {

	                start += child->parse();
	            }
            }
            return start;
        }
        case WHITE:
            return "W";
        
        default:
            return "B";
    }
    
}


octree::Octree::Octree(const std::shared_ptr<Primitive> &primitive, int depth) : rootNode(
        std::make_shared<Node>(primitive->minMax())) {
    rootNode->makeTreeInit(primitive, depth-1);
}

std::string octree::Octree::parse() {
    return this->rootNode->parse();
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