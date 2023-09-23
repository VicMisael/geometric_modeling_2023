#version 430 compatibility

out vec4 FragColor;

varying vec3 ourColor;
varying vec2 TexCoord;

uniform sampler2D ourTexture;

uniform bool isText;

void main()
{
    //if(isText == true){
      //  FragColor = texture(ourTexture, TexCoord);
    //}else{
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    //}
    
} 