//
// Created by misae on 21/09/2023.
//

#ifndef OCTREE_MODEL_BOX_H
#define OCTREE_MODEL_BOX_H

#include <glm/vec3.hpp>
#include "Primitive.h"


class Box : public Primitive {
     glm::vec3 min_point;
     glm::vec3 max_point;

    bool isInsideBoundingBox(glm::vec3 point);

public:
    Box(const glm::vec3 _min_point, const glm::vec3 _max_point) : min_point(_min_point), max_point(_max_point) {}

    [[nodiscard]] octree::NodeType classify(BoundingBox boundingBox) const override;


    [[nodiscard]] BoundingBox minMax() const override {
        return {this->min_point, this->max_point};
    }

    void transform(glm::mat4x4 matrix) override;;

};


#endif //OCTREE_MODEL_BOX_H
