//
// Created by Misael on 08/09/2023.
//
#pragma once
#ifndef OCTREE_MODEL_OCTREE_H
#define OCTREE_MODEL_OCTREE_H


#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include <utility>

#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include <Octree/Primitive.h>

namespace octree
{
	const auto standardBoundingBox = BoundingBox::GenerateCubeByCenterAndSideLength(glm::vec3(0, 0, 0), 30);

	class Node : std::enable_shared_from_this<Node>
	{
	public:
		NodeType nodeType;
		BoundingBox boundingBox;
		bool isLeaf = true;
		std::shared_ptr<Node> children[8];
		bool isRoot = false;

		void makeTree(const std::shared_ptr<Primitive>& _primitive, int _depth);

		void makeTreeInit(const std::shared_ptr<Primitive>& _primitive, int _depth);

		int depth();

		float volume();

		std::string parse();

		void translate(glm::vec3 vec3);

		void scale(float size);

		glm::vec3 getCenter()
		{
			return boundingBox.center();
		}

		static std::shared_ptr<Node> intersection(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);

        static std::shared_ptr<Node> union_(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);

		explicit Node(BoundingBox box) : boundingBox(std::move(box))
		{
		};

		static std::shared_ptr<Node> standardize(const std::shared_ptr<Node>& node);

	private:
		static void copyTree(std::shared_ptr<Node> dest, std::shared_ptr<Node> src);

		void subdivide();

		static void intersectionHelper(const std::shared_ptr<Node>& result, const std::shared_ptr<Node>& a,
		                               const std::shared_ptr<Node>& b);

        static void unionHelper(const std::shared_ptr<Node>& result, const std::shared_ptr<Node>& a,
                                       const std::shared_ptr<Node>& b);
	};
	class Octree
	{
	private:


	public:
		std::shared_ptr<Node> rootNode;

		explicit Octree(std::shared_ptr<Node> root);
		explicit Octree(const std::shared_ptr<Primitive>& primitive, int depth);

		std::string parse();

		float volume();

		int depth();

		void scale(float size);

		void translate(glm::vec3 point);

        std::shared_ptr<Octree> octreeUnion(const std::shared_ptr<octree::Octree>& other) const;

		std::shared_ptr<Octree> octreeIntersection(const std::shared_ptr<octree::Octree>& other) const;
	};
}


void octree::Node::subdivide() {
    isLeaf = false;
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
            if (!isLeaf) {
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
    if (!isLeaf) {
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
    if (!isLeaf) {
        for (const auto &child: children) {
            child->translate(point);
        }
    }
}

void octree::Node::scale(float size) {
    auto matrix = glm::scale(glm::mat4x4(1.0f), glm::vec3(size));
    this->boundingBox.min = matrix * glm::vec4(this->boundingBox.min, 1);
    this->boundingBox.max = matrix * glm::vec4(this->boundingBox.max, 1);
    if (!isLeaf) {
        for (const auto &child: children) {
            child->scale(size);
        }
    }
}

int octree::Node::depth() {
    if (nodeType == GRAY) {
        int largestDepth = 0;
        for (const auto &child: children) {
            int depth = 1 + child->depth();
            if (depth > largestDepth)
                largestDepth = depth;
        }
        return largestDepth;
    }
    return 1;
}


void octree::Node::copyTree(std::shared_ptr<Node> dest, std::shared_ptr<Node> src) {
    for (int i = 0; i < 8; i++) {
        if (src->children[i]->nodeType != octree::GRAY) {
            const auto type = src->children[i]->nodeType;
            dest->children[i]->nodeType = type;
        } else {
            dest->children[i]->subdivide();
            dest->children[i]->nodeType = GRAY;
            copyTree(dest->children[i], src->children[i]);
        }
    }
}


std::shared_ptr<octree::Node> octree::Node::standardize(const std::shared_ptr<Node> &node) {
    if (node->isRoot) {
        auto newRoot = std::make_shared<Node>(standardBoundingBox);
        newRoot->nodeType = GRAY;
        newRoot->isRoot = true;
        newRoot->subdivide();
        copyTree(newRoot, node);
        return newRoot;
    }
}

std::shared_ptr<octree::Node>
octree::Node::intersection(const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b) {
    auto destination = std::make_shared<Node>(standardBoundingBox);
    const auto standardizedA = standardize(a);
    const auto standardizedB = standardize(b);
    destination->subdivide();
    destination->nodeType = GRAY;
    intersectionHelper(destination, standardizedA, standardizedB);
    return destination;
}

void octree::Node::intersectionHelper(const std::shared_ptr<Node> &result, const std::shared_ptr<Node> &a,
                                      const std::shared_ptr<Node> &b) {
    for (int i = 0; i < 8; i++) {
        //Ambos folhas
        if (a->children[i]->isLeaf && b->children[i]->isLeaf) {
            if (a->children[i]->nodeType == BLACK && b->children[i]->nodeType == BLACK) {
                result->children[i]->nodeType = BLACK;
            } else {
                result->children[i]->nodeType = WHITE;
            }
        } else if (a->children[i]->isLeaf ^ b->children[i]->isLeaf) {
            const auto nodeA = a->children[i];
            const auto nodeB = b->children[i];
            if (nodeA->nodeType == WHITE || nodeB->nodeType == WHITE) {
                result->children[i]->nodeType = WHITE;
            } else {
                result->children[i]->nodeType = GRAY;
                result->children[i]->subdivide();
                auto children = nodeA->nodeType == GRAY ? nodeA->children : nodeB->children;
                for (int j = 0; j < 8; j++) {
                    result->children[i]->children[j] = children[j];
                }
            }
        } else {
            result->children[i]->subdivide();
            result->children[i]->nodeType = GRAY;
            intersectionHelper(result->children[i], a->children[i], b->children[i]);
        }
    }
}

std::shared_ptr<octree::Node> octree::Node::union_(const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b) {

    auto destination = std::make_shared<Node>(standardBoundingBox);
    const auto standardizedA = standardize(a);
    const auto standardizedB = standardize(b);
    destination->subdivide();
    destination->nodeType = GRAY;
    unionHelper(destination, standardizedA, standardizedB);
    return destination;
}

void octree::Node::unionHelper(const std::shared_ptr<Node> &result, const std::shared_ptr<Node> &a,
                               const std::shared_ptr<Node> &b) {

    for (int i = 0; i < 8; i++) {
        //Ambos folhas
        if (a->children[i]->isLeaf && b->children[i]->isLeaf) {
            if (a->children[i]->nodeType == BLACK || b->children[i]->nodeType == BLACK) {
                result->children[i]->nodeType = BLACK;
            } else {
                result->children[i]->nodeType = WHITE;
            }
        } else if (a->children[i]->isLeaf ^ b->children[i]->isLeaf) {
            //If one the nodes is leaf, copy one to the other
            if (a->children[i]->nodeType == BLACK || b->children[i]->nodeType == BLACK) {
                result->children[i]->nodeType = BLACK;
            } else {
                const auto nodeA = a->children[i];
                const auto nodeB = b->children[i];
                result->children[i]->nodeType = GRAY;
                result->children[i]->subdivide();
                auto children = nodeA->nodeType == GRAY ? nodeA->children : nodeB->children;
                for (int j = 0; j < 8; j++) {
                    result->children[i]->children[j] = children[j];
                }
            }
        } else {
            result->children[i]->subdivide();
            result->children[i]->nodeType = GRAY;
            unionHelper(result->children[i], a->children[i], b->children[i]);
        }
    }
}


octree::Octree::Octree(const std::shared_ptr<Primitive> &primitive, int depth) : rootNode(
        std::make_shared<Node>(primitive->cubedBoundingBox())) {
    rootNode->makeTreeInit(primitive, depth - 1);
    rootNode->isRoot = true;
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

int octree::Octree::depth() {
    return rootNode->depth();
}

std::shared_ptr<octree::Octree> octree::Octree::octreeIntersection(const std::shared_ptr<octree::Octree> &other) const {
    std::shared_ptr<Node> Result = Node::intersection(this->rootNode, other->rootNode);
    return std::make_shared<octree::Octree>(Result);
}

octree::Octree::Octree(const std::shared_ptr<Node> root) : rootNode(root) {
}

std::shared_ptr<octree::Octree> octree::Octree::octreeUnion(const std::shared_ptr<octree::Octree> &other) const {
    std::shared_ptr<Node> Result = Node::union_(this->rootNode, other->rootNode);
    return std::make_shared<octree::Octree>(Result);
}

#endif //OCTREE_MODEL_OCTREE_H
