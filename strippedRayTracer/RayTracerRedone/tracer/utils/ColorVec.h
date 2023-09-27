#pragma once

#include <glm/vec4.hpp>


class ColorVec : public glm::vec4 {
private:

public:
    void fixNans();

    constexpr ColorVec() : glm::vec4(0, 0, 0, 1) {};

    constexpr ColorVec(glm::vec4 vec) : glm::vec4(vec) {};

    constexpr ColorVec(float r, float g, float b) : glm::vec4(r, g, b, 1.0f) {
        glm::vec4(r,g,b,1.0f);
    };

    constexpr ColorVec(float r, float g, float b, float a) : glm::vec4(r, g, b, a) {};

    void clamp_to_x_if_bigger_than(float x, float val) {
        this->r = this->r > x ? val : this->r;
        this->g = this->g > x ? val : this->g;
        this->b = this->b > x ? val : this->b;
    }
    ColorVec powc(float power) const ;
};

