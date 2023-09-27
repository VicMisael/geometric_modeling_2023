//
// Created by Misael on 31/05/2023.
//
#include "TexturedMaterial.h"
#include "../../utils/Intersection.h"

ColorVec
TexturedMaterial::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    return texture_->value(intersection.u,intersection.v,intersection.hit_point)*this->material_->shade(world,ray,intersection,depth);
}

MaterialType TexturedMaterial::getMaterialType() {
    return MaterialType::TEXTURE;
}
