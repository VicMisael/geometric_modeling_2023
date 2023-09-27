#pragma once
#include "../utils/Types.h"
#include <tuple>
class ViewPlane
{
public:
	const uint32_t wsize;
	const uint32_t hsize;
	const float zw;
	const float pixelsize;	

	ViewPlane(uint32_t _hsize, uint32_t _vsize,float _zw, float _pixelsize);
};

