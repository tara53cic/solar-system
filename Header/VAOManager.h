#pragma once
#include <GL/glew.h>

void formVAOs(
    float* verticesBackground, size_t rectSize, unsigned int& VAOrect,
    float* verticesNametag, size_t nametagSize, unsigned int& VAOnametag,
    float* verticesdistanceBackground, size_t distanceBackgroundSize, unsigned int& VAOdistanceBackground,
    float* verticesRocket, size_t rocketSize, unsigned int& VAOrocket
);
