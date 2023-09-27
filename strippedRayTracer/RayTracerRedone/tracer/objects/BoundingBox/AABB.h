//
// Created by misae on 30/05/2023.
//

#pragma once

#include <glm/common.hpp>
#include <memory>
#include "../../scene//Ray.h"
#include "../../utils/Types.h"

class AABB {
    const Point3 min_;
    const Point3 max_;
public:
    AABB() = delete;

    AABB(const Point3 min, const Point3 max) : min_(min), max_(max) {};

    bool intersects(const Ray &ray) const;

    bool intersects(const Ray &ray, float &t_min) const;

    bool intersects(const Ray &ray, float &t_min, float &t_max) const;

    static std::shared_ptr<AABB> surrounding_box(const std::shared_ptr<AABB> box0, const std::shared_ptr<AABB> box1) {
        const auto minPoint = glm::min(box0->min(), box1->min());
        const auto maxPoint = glm::max(box0->max(), box1->max());
        return std::make_shared<AABB>(minPoint, maxPoint);
    };

    [[nodiscard]] Point3 min() const {
        return min_;
    }

    [[nodiscard]] Point3 max() const {
        return max_;
    }
};

