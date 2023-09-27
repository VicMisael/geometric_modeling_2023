//
// Created by Misael on 19/06/2023.
//

#include "imagecanvas.h"
#include <iostream>
#include "stb/image_canvas_stb_image.h"


void drawBar(float progress) {
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();

}


void imagecanvas::write_pixel(const uint16_t x, const uint16_t y, const ColorRGBA colorrgba) {
    float progress = static_cast<float>((y * this->width + x)) / totalPixels;
    drawBar(progress);
    this->rgba[y * this->width + x] = colorrgba.toRgba().rgba;
}

void imagecanvas::draw() {
    std::cout << std::endl;
    int width = (int) this->width;
    int height = (int) this->height;
    int channels = 4;
    auto const data = rgba;

    const std::string name = filename + ".png";
    stbi_write_png(name.c_str(), width, height, channels, data, width * 4);
}


