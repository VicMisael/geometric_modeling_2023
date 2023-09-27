//
// Created by Misael on 31/05/2023.
//

#include "CheckerTexture.h"

ColorVec CheckerTexture::value(float u, float v, const Point3& p) const {
   
     const int us = floor(u * size_);
     const int vs = floor(v * size_);
        //const int sizefloor = floor(size_);
        if ((us + vs)% 2 ==0) {
            return a_;
        }
        else {
            return b_;
        }
}
