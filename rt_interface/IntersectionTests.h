//
// Created by Misael on 26/09/2023.
//

#ifndef OCTREE_MODEL_INTERSECTIONTESTS_H
#define OCTREE_MODEL_INTERSECTIONTESTS_H

#include <optional>
#include "../strippedRayTracer/RayTracerRedone/tracer/utils/Intersection.h"
#include "../strippedRayTracer/RayTracerRedone/tracer/scene/Ray.h"

namespace RTUtils {

    std::optional<intersectionRec>
    processBoundingBoxIntersection(const Ray &ray,const glm::vec3 &min, const glm::vec3 &max, const std::shared_ptr<Material>& material) ;

    bool checkIntersection(const Ray &ray);

} // RTUtils

#endif //OCTREE_MODEL_INTERSECTIONTESTS_H
