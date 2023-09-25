#version 430 compatibility

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aText;

varying vec3 ourColor;
varying vec2 TexCoord;

uniform mat4 transform;

void main()
{
    ourColor = aColor;
    TexCoord = aText;
    gl_Position = vec4(aPos, 1.0);
}