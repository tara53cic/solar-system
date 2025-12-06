#version 330 core

layout(location = 0) in vec2 inPos;   
layout(location = 1) in vec2 inTex;   
out vec2 chTex;                        

uniform vec2 uPos;      
uniform float uRot; 

void main()
{
    gl_Position = vec4(inPos + uPos, 0.0, 1.0);

    vec2 centered = inTex - 0.5;

    float cosR = cos(uRot);
    float sinR = sin(uRot);
    vec2 rotated;
    rotated.x = centered.x * cosR - centered.y * sinR;
    rotated.y = centered.x * sinR + centered.y * cosR;

    chTex = rotated + 0.5;
}


