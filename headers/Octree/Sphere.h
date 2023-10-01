//
// Created by misae on 21/09/2023.
//
#pragma once

#ifndef OCTREE_MODEL_SPHERE_H
#define OCTREE_MODEL_SPHERE_H


#include <glm/vec3.hpp>

#include <Octree/Primitive.h>

class Sphere : public Primitive {
    glm::vec3 center;
    float radius;
public:
    explicit Sphere(float radius) : center(glm::vec3(0, 0, 0)), radius(radius) {}

    explicit Sphere() : center(glm::vec3(0, 0, 0)), radius(1.0f ) {}

    octree::NodeType classify(BoundingBox boundingBox) const override;

    BoundingBox cubedBoundingBox() const override;

    void transform(glm::mat4x4 matrix) override;

};


BoundingBox Sphere::cubedBoundingBox() const {

//    return {center - glm::vec3( radius),
//            center + glm::vec3( radius)};

    return BoundingBox::GenerateCubedBoundingBox(center - glm::vec3(radius), center + glm::vec3(radius));
}

void Sphere::transform(glm::mat4x4 matrix) {
    center = matrix * glm::vec4(center, 1);
}

octree::NodeType Sphere::classify(BoundingBox boundingBox) const {


    auto vertexes = boundingBox.generateCubeVertices();
    int cornersInsideCount = 0;
    for (const auto &vertice: vertexes) {
        if (length(vertice - center) <= radius) {
            cornersInsideCount++;
        }
    }
    if (cornersInsideCount == 8) return octree::BLACK;
    if (cornersInsideCount > 0) return octree::GRAY;
    return octree::WHITE;

}

#endif //OCTREE_MODEL_SPHERE_H
