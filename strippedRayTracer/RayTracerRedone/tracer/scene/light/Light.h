#pragma once
#include "../../utils/Types.h"
#include "../../utils/ColorVec.h"
class Light
{
protected:
	float intensity;
	ColorVec color = ColorVec(1, 1, 1);

	Light(const float _intensity, const ColorVec _color) :intensity(_intensity), color(_color) {}
public:
	virtual ~Light() = default;

	Light() = delete;
	float getIntensity() const
	{
		return intensity;
	}

	ColorVec getColor() const
	{
		return color;
	};

};

