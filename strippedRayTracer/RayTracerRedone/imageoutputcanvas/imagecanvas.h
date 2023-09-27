//
// Created by Misael on 19/06/2023.
//

#ifndef RAYTRACER_REDONE_IMAGECANVAS_H
#define RAYTRACER_REDONE_IMAGECANVAS_H

#include <utility>
#include<string>
#include "../tracer/scene/Canvas.h"


class imagecanvas : public Canvas {
    uint32_t *rgba;

    const long totalPixels;
    std::string filename;
public:


    imagecanvas(const uint32_t w, const uint32_t h, const std::string name) : Canvas(w, h), totalPixels(w * h),
                                                                              filename(name) {
        rgba = new uint32_t[w * h];
#ifdef _MSC_VER
        setvbuf(stdout, 0, _IOLBF, 8192);
#endif
    }

    void write_pixel(const uint16_t x, const uint16_t y, const ColorRGBA colorrgba) override;

    void draw() override;

};


#endif //RAYTRACER_REDONE_IMAGECANVAS_H
