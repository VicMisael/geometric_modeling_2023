//
// Created by Misael on 03/06/2023.
//

#pragma once

#include "Phong.h"
#include "../textures/Texture.h"
#include "../BxDF/PerfectSpecular.h"

//Handle the edge case of black textures
class TexturedPhongReflective: public Phong {
    std::shared_ptr<Texture> texture_;
    PerfectSpecular reflective_brdf;
public:
    explicit TexturedPhongReflective(std::shared_ptr<Texture> texture,const float r):Phong(Constants::WHITE, Constants::WHITE, 1, 1, 25),
    texture_(std::move(texture)),
    reflective_brdf(r){
    }

    ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

    MaterialType getMaterialType() override {
        return MaterialType::TEXTURE;
    }
};


