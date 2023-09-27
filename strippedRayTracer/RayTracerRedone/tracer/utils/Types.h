#pragma once
#include "../config/glm_definitions.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>  
#include <glm/ext/vector_float4.hpp>
#include <glm/mat4x4.hpp>
#include <cstdint>

using Point3 = glm::vec3;
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Matrix4x4=glm::mat4x4;
using Matrix3x3=glm::mat3x3;

union RGBA {
    uint32_t rgba;
    struct {
        uint8_t  _r, _g, _b, _a;
    };
};
