#pragma once
#include <cstdint>
#include <memory>
#include "ViewPlane.h"
#include "../utils/ColorRGBA.h"
class Canvas
{	
protected:
	const uint32_t width;
	const uint32_t height;
public:

	Canvas(const uint32_t _w,const uint32_t _h):width(_w),height(_h){}

	float step_size_y(const std::shared_ptr<ViewPlane> viewPlane) const{
		return viewPlane->hsize / static_cast<float>(height);
	};
	float step_size_x(const std::shared_ptr<ViewPlane> viewPlane) const {
		return viewPlane->hsize / static_cast<float>(width);
	};
	uint32_t getWidth() const {
		return width;
	}
	uint32_t getHeight() const {
		return height;
	}
	virtual void write_pixel(const uint16_t x, const uint16_t y,const ColorRGBA colorrgba) = 0;
	virtual void draw()=0;
};

