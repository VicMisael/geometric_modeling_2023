//
// Created by Misael on 31/05/2023.
//

#include "TexturedMatte.h"

ColorVec
TexturedMatte::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    return texture_->value(intersection.u,intersection.v,intersection.hit_point) * Matte::shade(world, ray, intersection, depth);
}

MaterialType TexturedMatte::getMaterialType() {
    return MaterialType::TEXTURE;
}
