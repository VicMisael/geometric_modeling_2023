//
// Created by Misael on 16/06/2023.
//

#pragma once

#include "BxDF.h"
#include "../../scene/Ray.h"

class BTDF : public BxDF {
public:
    virtual float internal_reflection(const Vector3 &wo, const intersectionRec &intersection) const= 0;
};


