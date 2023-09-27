//
// Created by Misael on 05/06/2023.
//

#pragma once

#include <glm/ext/matrix_transform.hpp>
#include "../utils/Types.h"

class Camera {
public:
    Camera( const Vector3 &eye, const Vector3 &lookAt,const Vector3 &up) : up(up), look_at(lookAt), eye(eye) {
        lookAtMatrix = glm::lookAt(eye, look_at, up);
    }

    Camera() {
        lookAtMatrix=Matrix4x4(1.0f);
        nocam = true;
       
    };

    [[nodiscard]] Matrix4x4 getLookAtInverse() const {
        return glm::inverse(lookAtMatrix);
    }

private:
    bool nocam = 0;
    Vector3 up;
    Vector3 look_at;
    Vector3 eye;
    Matrix4x4 lookAtMatrix;

};

