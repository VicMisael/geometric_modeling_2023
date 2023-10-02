#pragma once


#ifndef VERTEX_H
#define VERTEX_H

#include<glm/vec3.hpp>
#include<glm/vec2.hpp>

struct Vertex
{
    //glm::vec3 position;
    float px;
    float py;
    float pz;
    // normals
    float nx;
    float ny;
    float nz;
    //glm::vec2 textCoord;
    float tx;
    float ty;
};

#endif