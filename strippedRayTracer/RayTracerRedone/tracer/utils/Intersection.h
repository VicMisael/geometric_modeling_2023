#pragma once
#include <memory>
#include "Types.h"


class Material;

struct intersectionRec
{
	const float tmin;
	const Point3 hit_point;
    Vector3 normal;
    std::shared_ptr<Material> material;
    const float u=0;
    const float v=0;
};

