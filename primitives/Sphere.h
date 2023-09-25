//
// Created by misae on 21/09/2023.
//
#pragma once
#ifndef OCTREE_MODEL_SPHERE_H
#define OCTREE_MODEL_SPHERE_H


#include <glm/vec3.hpp>

#include "Primitive.h"

class Sphere: public Primitive {
	glm::vec3 center;
	float radius;
public:
	Sphere(glm::vec3 center, float radius): center(center), radius(radius){}

    octree::NodeType classify(BoundingBox boundingBox) ;
    BoundingBox minMax() override;

    void transform(glm::mat4x4 matrix) override;

};


BoundingBox Sphere::minMax() {

    return {center - glm::vec3( radius),
            center + glm::vec3( radius)};
}

void Sphere::transform(glm::mat4x4 matrix) {
    center = matrix * glm::vec4(center, 1);
}

octree::NodeType Sphere::classify(BoundingBox boundingBox) {


    auto vertexes = boundingBox.generateCubeVertices();
    int cornersInsideCount = 0;
    for (const auto &vertice: vertexes) {
        if (glm::length(vertice - center) < radius) {
            cornersInsideCount++;
        }
    }
    if (cornersInsideCount == 8) return octree::BLACK;
    if (cornersInsideCount > 0) return octree::GRAY;
    return octree::WHITE;

}




#endif //OCTREE_MODEL_SPHERE_H
