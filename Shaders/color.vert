#version 330 core
layout(location = 0) in vec2 inPos;
out vec3 color;

void main()
{
    gl_Position = vec4(inPos, 0.0, 1.0);
    color = vec3(1.0, 0.0, 0.0); // temporary: red color
}
