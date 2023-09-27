//
// Created by Misael on 13/07/2023.
//

#pragma once

#include "Material.h"

//It's like a black hole, Absorbs everything, nothing gets out
class NullMaterial : public Material {
public:
    ColorVec
    shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

};
