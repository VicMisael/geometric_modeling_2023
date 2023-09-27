#pragma once


#include "Texture.h"
#include "../../utils/Constants.h"

class CheckerTexture: public Texture{
protected:
    const ColorVec a_;
    const ColorVec b_;
    const float size_;
public:
    CheckerTexture():CheckerTexture(10){};
    CheckerTexture(const float size):CheckerTexture(Constants::RED,Constants::WHITE,size){};
    CheckerTexture(const ColorVec a,const ColorVec b):CheckerTexture(a,b, 10) {

    }
    CheckerTexture(const ColorVec a,const ColorVec b,const float size):a_(a),b_(b),size_(size){

    }
    [[nodiscard]] ColorVec value(float u, float v, const Point3& p) const override;
};



