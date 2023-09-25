//
// Created by misae on 21/09/2023.
//
#pragma once
#ifndef OCTREE_MODEL_BOX_H
#define OCTREE_MODEL_BOX_H
#include <glm/vec3.hpp>

#include "Primitive.h"


class Box: public Primitive {
	const glm::vec3 min_point;
	const glm::vec3 max_point;

public:
	Box(glm::vec3 _min_point,glm::vec3 _max_point):min_point(_min_point),max_point(_max_point){};
};


#endif //OCTREE_MODEL_BOX_H
