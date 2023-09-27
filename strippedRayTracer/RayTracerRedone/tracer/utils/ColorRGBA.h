#pragma once
#include "ColorVec.h"
#include <cstdint>
#include "Types.h"
typedef glm::vec<4, uint8_t, glm::defaultp> bytevec4;
class ColorRGBA:public bytevec4
{
private:
public:

	explicit ColorRGBA(const ColorVec _color) :bytevec4
		(
		_color.r > 1.0f ? 255 : _color.r*255,
		_color.g > 1.0f ? 255 : _color.g*255,
		_color.b > 1.0f ? 255 : _color.b*255,
		255//_color.a > 1.0f ? 255 : _color.a*255
		) {};

	explicit ColorRGBA(const RGBA _color) :bytevec4
	(
		_color._r,
		_color._g,
		_color._b,
		_color._a
	) {};

	RGBA toRgba() const {
		RGBA rgba;
		rgba._r = r;
		rgba._g = g;
		rgba._b = b;
		rgba._a = a;
		return rgba;
	}
};

