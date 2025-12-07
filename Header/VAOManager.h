#pragma once
#include <GL/glew.h>

void formVAOs(

    // Background rectangle
    float* verticesBackground, size_t rectSize, unsigned int& VAOrect,

    // Nametag
    float* verticesNametag, size_t nametagSize, unsigned int& VAOnametag,

    // Distance background
    float* verticesTopLeftRect, size_t distanceBackgroundSize, unsigned int& VAOdistanceBackground,

    // Rocket
    float* verticesRocket, size_t rocketSize, unsigned int& VAOrocket,

    // Pluto icon
    float* verticesPlutoIcon, size_t plutoIconSize, unsigned int& VAOplutoIcon,

    // Mercury icon
    float* verticesMercuryIcon, size_t mercuryIconSize, unsigned int& VAOmercuryIcon,

    // Venus icon
    float* verticesVenusIcon, size_t venusIconSize, unsigned int& VAOvenusIcon,

    // Mars icon
    float* verticesMarsIcon, size_t marsIconSize, unsigned int& VAOmarsIcon,

    // Jupiter icon
    float* verticesJupiterIcon, size_t jupiterIconSize, unsigned int& VAOjupiterIcon,

    // Saturn icon
    float* verticesSaturnIcon, size_t saturnIconSize, unsigned int& VAOsaturnIcon,

    // Uranus icon
    float* verticesUranusIcon, size_t uranusIconSize, unsigned int& VAOuranusIcon,

    // Neptune icon
    float* verticesNeptuneIcon, size_t neptuneIconSize, unsigned int& VAOneptuneIcon
);
