//
// Created by misae on 21/09/2023.
//

#ifndef OCTREE_MODEL_SPHERE_H
#define OCTREE_MODEL_SPHERE_H


#include <glm/vec3.hpp>

#include "Primitive.h"

class Sphere: public Primitive {
	glm::vec3 center;
	float radius;
public:
	Sphere(glm::vec3 center, float radius): center(center), radius(radius){}

    octree::NodeType classify(BoundingBox boundingBox) const override ;
    BoundingBox minMax()  const override;

    void transform(glm::mat4x4 matrix) override;

};


#endif //OCTREE_MODEL_SPHERE_H
