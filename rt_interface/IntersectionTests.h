//
// Created by Misael on 26/09/2023.
//

#ifndef OCTREE_MODEL_INTERSECTIONTESTS_H
#define OCTREE_MODEL_INTERSECTIONTESTS_H

#include <optional>
#include "../strippedRayTracer/RayTracerRedone/tracer/utils/Intersection.h"
#include "../strippedRayTracer/RayTracerRedone/tracer/scene/Ray.h"

namespace RTUtils {
    struct rt_output {
        float tmin;
        glm::vec3 point;
        glm::vec3 normal;
        float u;
        float v;
        bool isset = false;
    };

    std::optional<rt_output>
    processBoundingBoxIntersection(const Ray &ray, const glm::vec3 &min, const glm::vec3 &max);

    bool intersects(const Ray &ray, const glm::vec3 &min, const glm::vec3 &max);
} // RTUtils

#endif //OCTREE_MODEL_INTERSECTIONTESTS_H
