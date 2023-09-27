#pragma once
#include "CheckerTexture.h"
class PointCheckerTexture:public CheckerTexture
{
public:
    PointCheckerTexture();
    PointCheckerTexture(const float size) :CheckerTexture(size){}
    PointCheckerTexture(const ColorVec a, const ColorVec b):CheckerTexture(a, b) {}
    PointCheckerTexture(const ColorVec a, const ColorVec b, const float size):CheckerTexture(a, b, size) {}
    [[nodiscard]] ColorVec value(float u, float v, const Point3& p) const override;
};

