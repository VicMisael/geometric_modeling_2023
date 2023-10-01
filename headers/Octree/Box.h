//
// Created by misae on 21/09/2023.
//
#pragma once
#ifndef OCTREE_MODEL_BOX_H
#define OCTREE_MODEL_BOX_H

#include <glm/vec3.hpp>
#include <Octree/Primitive.h>


class Box : public Primitive
{
	glm::vec3 min_point;
	glm::vec3 max_point;

	bool isInsideBoundingBox(glm::vec3 point) const;

public:
	Box(const glm::vec3 _min_point, const glm::vec3 _max_point) : min_point(_min_point), max_point(_max_point)
	{
	}

	Box(const glm::vec3 center, float length) : min_point(center - glm::vec3(length)),
	                                            max_point(center + glm::vec3(length))
	{

	};

	[[nodiscard]] octree::NodeType classify(BoundingBox boundingBox) const override;


	[[nodiscard]] BoundingBox cubedBoundingBox() const override;

	void transform(glm::mat4x4 matrix) override;;
};

bool Box::isInsideBoundingBox(glm::vec3 point) const  {
    return (point.x >= min_point.x && point.x <= max_point.x) &&
           (point.y >= min_point.y && point.y <= max_point.y) &&
           (point.z >= min_point.z && point.z <= max_point.z);
}

octree::NodeType Box::classify(BoundingBox boundingBox) const {
    const auto vertexes = boundingBox.generateCubeVertices();
    int insideCount = 0;
    for (const auto vertex: vertexes) {
        insideCount += isInsideBoundingBox(vertex);
    }
    if (insideCount == 8) return octree::BLACK;
    if (insideCount > 0) return octree::GRAY;
    return octree::WHITE;
}

BoundingBox Box::cubedBoundingBox() const
{
    //return { this->min_point,this->max_point };
    return BoundingBox::GenerateCubedBoundingBox(this->min_point, this->max_point);
}

void Box::transform(glm::mat4x4 matrix) {
    min_point = matrix * glm::vec4(min_point, 1);
    max_point = matrix * glm::vec4(max_point, 1);
}


#endif //OCTREE_MODEL_BOX_H
