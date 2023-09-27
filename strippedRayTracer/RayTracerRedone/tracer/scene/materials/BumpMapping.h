//
// Created by Misael on 21/06/2023.
//

#pragma once


#include <memory>
#include "Material.h"
#include "../textures/Texture.h"

/*
 * The object must support uv mapping;
 */
class BumpMapping: public Material {
public:
    BumpMapping()=delete;

    BumpMapping(const std::shared_ptr<Material> &material, const std::shared_ptr<Texture> &normalMap) : material(
            material), normal_map(normalMap) {}

    ColorVec shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const override;


private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Texture> normal_map;
};


