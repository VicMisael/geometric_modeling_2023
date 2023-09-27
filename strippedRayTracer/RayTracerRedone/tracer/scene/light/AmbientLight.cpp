#include "AmbientLight.h"

ColorVec AmbientLight::intensityAtPoint(const Point3) const
{
    return intensity * color;
}
