//
// Created by Misael on 13/07/2023.
//

#include "NullMaterial.h"

ColorVec
NullMaterial::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    return ColorVec();
}
