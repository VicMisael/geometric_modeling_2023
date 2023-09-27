//
// Created by Misael on 23/06/2023.
//
#include "ColorVec.h"
#include <glm/exponential.hpp>
#include <cmath>

ColorVec ColorVec::powc(float power) const {
    //  return glm::pow(*this, vec4(power));
    return {powf(r, power), powf(g, power), powf(b, power), 1.0f};
}

void ColorVec::fixNans() {
    this->r = std::isnan(this->r) ? 0 : this->r;
    this->g = std::isnan(this->g) ? 0 : this->g;
    this->b = std::isnan(this->b) ? 0 : this->b;
}
