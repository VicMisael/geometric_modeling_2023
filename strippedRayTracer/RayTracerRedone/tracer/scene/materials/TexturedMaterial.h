//
// Created by Misael on 31/05/2023.
//

#pragma once

#include <memory>
#include "Material.h"
#include "../textures/Texture.h"

//Avoid This
class TexturedMaterial: public Material{
    std::shared_ptr<Texture> texture_;
    std::shared_ptr<Material> material_;
public:
    TexturedMaterial(std::shared_ptr<Texture> texture,std::shared_ptr<Material> _material):texture_(texture),material_(_material){

    };

    ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;

    MaterialType getMaterialType() override;

};



