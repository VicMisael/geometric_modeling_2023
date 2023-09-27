//
// Created by Misael on 24/06/2023.
//

#pragma once

#include "Material.h"



class DiffuseLight : public Material {
    const ColorVec color;
    const float intensity;
public:
    DiffuseLight(const ColorVec &color, float intensity);

    ColorVec
    shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

    ColorVec getL() const;
    bool castShadow() const override { return false; }

};


