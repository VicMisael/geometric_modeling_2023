//
// Created by Misael on 31/05/2023.
//
#pragma once
#include "Matte.h"

#include <utility>
#include "../textures/Texture.h"

class TexturedMatte: public Matte{
    std::shared_ptr<Texture> texture_;
public:
    explicit TexturedMatte(std::shared_ptr<Texture> texture): Matte(1,Constants::WHITE),texture_(std::move(texture)){
    }
    TexturedMatte(std::shared_ptr<Texture> texture,const float kd): Matte(kd,Constants::WHITE),texture_(std::move(texture)){
    }
    TexturedMatte(std::shared_ptr<Texture> texture,const Matte _matte): Matte(_matte),texture_(std::move(texture)){
    }

    ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

    MaterialType getMaterialType() override;

};



