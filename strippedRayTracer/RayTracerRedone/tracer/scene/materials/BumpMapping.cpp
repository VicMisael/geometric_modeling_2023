//
// Created by Misael on 21/06/2023.
//

#include <glm/gtx/norm.hpp>
#include "BumpMapping.h"
#include "../../utils/Intersection.h"
#include "../../utils/OrthonormalBase.h"
#include "../../utils/utility.h"
#include <iostream>

ColorVec
BumpMapping::shade(const World &world, const Ray &ray, const intersectionRec &intersectionIn, int32_t depth) const {
    auto col = normal_map->value(intersectionIn.u, intersectionIn.v, intersectionIn.hit_point);
    Vector3 normal = normalize(intersectionIn.normal);
    const Vector3 bumpMapping = (2.0f * Vector3(col)) - Vector3(1.0f);


    normal = utility::ONBTransform(normal,bumpMapping);
    const auto intersection = intersectionRec{intersectionIn.tmin, intersectionIn.hit_point, normal, intersectionIn.material,
                                        intersectionIn.u, intersectionIn.v};
    return this->material->shade(world, ray, intersection, depth);

}
