#pragma once
#include <GL/glew.h>

void drawBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawNametag(unsigned int shader, unsigned int vao, unsigned int tex);
void drawDistanceBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawRocket(unsigned int rocketShader, unsigned int VAOrocket, unsigned int rocketTexture, float uX, float uY, float uRot);
#pragma once
