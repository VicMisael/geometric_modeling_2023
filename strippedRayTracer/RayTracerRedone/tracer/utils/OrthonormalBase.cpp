//
// Created by Misael on 12/07/2023.
//

#include "OrthonormalBase.h"

OrthonormalBase::OrthonormalBase(Vector3 W) {
    W = glm::normalize(W);
    Vector3 a =
            glm::length2(W - Vector3(0, 1, 0)) < glm::epsilon<float>() ? Vector3(1, 0, 0) : Vector3(0, 1, 0);

    Vector3 U = normalize(cross(W, a));
    Vector3 V = normalize(cross(W, U));
    UVW = Matrix3x3(U, V, W);
}

Vector3 OrthonormalBase::u() const {
    return UVW[0];
}

Vector3 OrthonormalBase::v() const {
    return UVW[1];
}

Vector3 OrthonormalBase::w() const {
    return UVW[2];
}

Point3 OrthonormalBase::local(const Point3 point) const {
    return UVW * point;
}

Matrix3x3 OrthonormalBase::onb() const {
    return UVW;
}
