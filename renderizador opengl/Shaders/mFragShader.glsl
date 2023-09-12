#version 430 compatibility

out vec4 FragColor;

varying vec3 ourColor;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

uniform bool isText;

void main()
{
    if(isText == true){
        FragColor = texture(ourTexture, TexCoord);
    }else{
        FragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);
    }
    
} 