//
// Created by misae on 30/05/2023.
//

#include "AABB.h"
#include <algorithm>


bool AABB::intersects(const Ray& ray) const
{
	float t_min = 0;
	float t_max = std::numeric_limits<float>::max();
	return this->intersects(ray, t_min, t_max);
}

bool AABB::intersects(const Ray& ray, float& t_min) const
{
	float t_max = std::numeric_limits<float>::max();
	return this->intersects(ray, t_min, t_max);
}

bool AABB::intersects(const Ray& ray, float& t_min, float& t_max) const
{

	const auto& dir = ray.direction;
	const auto invD = Vector3(1 / dir.x, 1 / dir.y, 1 / dir.z);
	const auto t0s = (min_ - ray.origin) * invD;
	const auto t1s = (max_ - ray.origin) * invD;

	const Vector3 smaller = glm::min(t0s, t1s);
	const Vector3 bigger = glm::max(t0s, t1s);

	t_min = std::max(t_min, std::max(smaller.x, std::max(smaller.y, smaller.z)));
	t_max = std::min(t_max, std::min(bigger.x, std::min(bigger.y, bigger.z)));

	return (t_min < t_max);

	/*
	for (int a = 0; a < 3; a++)
	{
		auto invD = 1.0f / ray.direction[a];
		auto t0 = (min()[a] - ray.origin[a]) * invD;
		auto t1 = (max()[a] - ray.origin[a]) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min)
			return false;
	}
	return true;
    */
}
