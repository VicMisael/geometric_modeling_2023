//
// Created by misae on 03/06/2023.
//

#pragma once


#include <string>
#include "Texture.h"

class ImageTexture: public Texture{
public:
    const static int bytes_per_pixel = 3;
    virtual ~ImageTexture();
    ImageTexture():data(nullptr),width(0),height(0),bytes_per_scanline(0){}
    ImageTexture(const std::string& filename);
    ColorVec value(float u, float v, const Point3 &p) const override;

private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;

};

