//
// Created by Misael on 12/07/2023.
//

#pragma once

#include <glm/gtx/norm.hpp>
#include "Types.h"

class OrthonormalBase {
    Matrix3x3 UVW{};
public:
    OrthonormalBase() = delete;

    explicit OrthonormalBase(Vector3 W) ;

    [[nodiscard]] Vector3 u() const;

    [[nodiscard]] Vector3 v() const ;

    [[nodiscard]] Vector3 w() const ;

    [[nodiscard]] Matrix3x3 onb() const;

    Point3 local(const Point3 point) const;
};

