#version 430 compatibility

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aText;

varying vec3 ourColor;
varying vec2 TexCoord;

void main()
{
    ourColor = aColor;
    TexCoord = aText;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}