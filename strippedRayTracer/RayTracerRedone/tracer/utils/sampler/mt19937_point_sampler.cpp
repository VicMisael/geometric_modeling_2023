#include "mt19937_point_sampler.h"
#include <glm/vec2.hpp>

inline std::tuple<float, float> mt19937_point_sampler::generate_random_point()
{
	return {dis(generator), dis(generator)};
}

std::vector<std::tuple<float, float>> mt19937_point_sampler::generate_points()
{
	std::vector<std::tuple<float, float>> points;
	points.reserve(num_samples);
	for (int i = 1; i <= num_samples; i++)
	{
		points.emplace_back(generate_random_point());
	}
	return points;
}
