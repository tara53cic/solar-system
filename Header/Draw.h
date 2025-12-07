#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <cmath> 

void drawBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawNametag(unsigned int shader, unsigned int vao, unsigned int tex);
void drawDistanceBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawRocket(unsigned int rocketShader, unsigned int VAOrocket, unsigned int rocketTexture, float uX, float uY, float uRot);
void drawAlienIcon(unsigned int alienIconShader, unsigned int VAOalienIcon, unsigned int alienIconTexture);

//?uvamo poziciju vanzemaljca
struct Vec2 { float x, y; };
Vec2 drawAlien (unsigned int alienShader, unsigned int VAOalien, unsigned int alienTexture);
#pragma once
