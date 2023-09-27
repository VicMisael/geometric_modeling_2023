//
// Created by Misael on 31/05/2023.
//

#pragma once


#include "Phong.h"

#include <utility>
#include "../textures/Texture.h"

class TexturedPhong: public Phong {
    std::shared_ptr<Texture> texture_;
public:

    explicit TexturedPhong(std::shared_ptr<Texture> texture) :Phong(Constants::WHITE, Constants::WHITE, 1, 1, 25),
    texture_(std::move(texture)){
    }

    TexturedPhong(std::shared_ptr<Texture> texture,Phong _phong): Phong(std::move(_phong)),texture_(std::move(texture)){

    }

    TexturedPhong(std::shared_ptr<Texture> texture,float kspecular,float exp) :Phong(Constants::WHITE, Constants::WHITE, kspecular, 1, exp),
                                                     texture_(std::move(texture)){

    }

    ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

    MaterialType getMaterialType() override;
};


