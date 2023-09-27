#include "PointCheckerTexture.h"

ColorVec PointCheckerTexture::value(float u, float v, const Point3& p) const
{
    const float eps = -0.001;
    const float x = p.x + eps;
    const float y = p.y + eps;
    const float z = p.z + eps;

    if (((int)floor(x / size_) + (int)floor(y / size_) + (int)floor(z /
        size_)) % 2 == 0)
        return a_;
    else
        return b_;
}
