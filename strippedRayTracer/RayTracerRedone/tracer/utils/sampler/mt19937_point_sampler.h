#pragma once
#include "sampler.h"
#include <random>

class mt19937_point_sampler : public sampler
{
	std::mt19937 generator;
	std::uniform_real_distribution<float> dis;
	std::tuple<float, float> generate_random_point();

public:
	mt19937_point_sampler(const unsigned int num) : sampler(num), dis(0.0f, 1.0f)
	{
	};
	std::vector<std::tuple<float, float>> generate_points() final;
};
