#pragma once

#include <random>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/random.hpp>

#include "Constants.h"
#include "Types.h"


namespace utility {
    //static std::mt19937 generator;
    //A counter, for debugging reasons, leave it there

     Vector3 random();

     double random_double();

    [[maybe_unused]]  float inversesqrt(float x);

//	 float dot_product_intrinsic(Vector3 a, Vector3 b) {
//		__m128 lhs = _mm_set_ps(a.x, a.y, a.z, 0);
//		__m128 rhs = _mm_set_ps(b.x, b.y, b.z, 0);
//		const auto result = _mm_dp_ps(lhs, rhs, 0xFF);
//		return _mm_cvtss_f32(result);
//	};

     Vector3 random(float min, float max);

     Vector3 ONBTransform(Vector3 W, Vector3 in);

     float random_in_interval(float min, float max);

     Vector3 random_in_unit_sphere();

     Vector3 random_in_hemisphere();

     Vector3 random_in_hemisphere(const Vector3 normal);

     float clamp(float x, float min, float max);

     Vector2 random_unit_square();

     Vector3 random_unit_cube();

     Vector3 reflect_vector(const Vector3 in, const Vector3 normal);
}

