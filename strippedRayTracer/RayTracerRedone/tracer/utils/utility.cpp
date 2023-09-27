//
// Created by Misael on 15/07/2023.
//
#include "utility.h"

#include <glm/gtx/norm.hpp>


std::mt19937 generator(time(NULL));

Vector3 utility::random() {

    std::uniform_real_distribution<float> dis;
    //std::uniform_int_distribution<float> dist();
    return {dis(generator), dis(generator), dis(generator)};
}

double utility::random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

[[maybe_unused]] float utility::inversesqrt(float x) {
    return glm::inversesqrt(x);
}

//	float dot_product_intrinsic(Vector3 a, Vector3 b) {
//		__m128 lhs = _mm_set_ps(a.x, a.y, a.z, 0);
//		__m128 rhs = _mm_set_ps(b.x, b.y, b.z, 0);
//		const auto result = _mm_dp_ps(lhs, rhs, 0xFF);
//		return _mm_cvtss_f32(result);
//	};

Vector3 utility::random(float min, float max) {
    std::uniform_real_distribution dis(min, max);
    //std::uniform_int_distribution<float> dist();
    return {dis(generator), dis(generator), dis(generator)};
}

Vector3 utility::ONBTransform(Vector3 W, Vector3 in)
{
    W = glm::normalize(W);
    const Vector3 a =
        glm::length2(W - Vector3(0, 1, 0)) < glm::epsilon<float>() ? Vector3(1, 0, 0) : Vector3(0, 1, 0);

    const Vector3 U = normalize(cross(W, a));
    const Vector3 V = normalize(cross(W, U));
    const Matrix3x3 UVW = Matrix3x3(U, V, W);
    return UVW * in;
}

float utility::random_in_interval(float min, float max) {
    std::uniform_real_distribution dis(min, max);
    return dis(generator);
}

Vector3 utility::random_in_unit_sphere() {

//		auto r1 = random_double();
//		auto r2 = random_double();
//		auto x = cos(2 * Constants::pi * r1) * 2 * sqrt(r2 * (1 - r2));
//		auto y = sin(2 * Constants::pi * r1) * 2 * sqrt(r2 * (1 - r2));
//		auto z = 1 - r2;
//		return Vector3(x, y, z);

    return glm::sphericalRand(1.0f);
}

Vector3 utility::random_in_hemisphere() {
   return random_in_hemisphere( Vector3(0, 1, 0));
}
Vector3 utility::random_in_hemisphere(const Vector3 normal) {
    Vector3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    return -in_unit_sphere;
}

float utility::clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

Vector2 utility::random_unit_square() {
    return {random_in_interval(0, 1), random_in_interval(0, 1)};
}

Vector3 utility::random_unit_cube() {
    return {random_in_interval(0, 1), random_in_interval(0, 1), random_in_interval(0, 1)};
}

Vector3 utility::reflect_vector(const Vector3 in, const Vector3 normal) {
    return glm::reflect(in, normal);
    //return in-2*dot(in,normal)*normal;
}