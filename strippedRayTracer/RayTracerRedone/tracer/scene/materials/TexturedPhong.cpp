//
// Created by Misael on 31/05/2023.
//

#include "TexturedPhong.h"

ColorVec
TexturedPhong::shade(const World &world, const Ray &ray, const intersectionRec &intersection, int32_t depth) const {
    return texture_->value(intersection.u, intersection.v, intersection.hit_point) *
           Phong::shade(world, ray, intersection, depth);
}

MaterialType TexturedPhong::getMaterialType() {
    return MaterialType::TEXTURE;
}
