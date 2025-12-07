#pragma once
#include <GL/glew.h>

void drawBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawNametag(unsigned int shader, unsigned int vao, unsigned int tex);
void drawDistanceBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawRocket(unsigned int rocketShader, unsigned int VAOrocket, unsigned int rocketTexture, float uX, float uY, float uRot);
void drawAlienIcon(unsigned int alienIconShader, unsigned int VAOalienIcon, unsigned int alienIconTexture);
#pragma once
