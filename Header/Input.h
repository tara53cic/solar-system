#pragma once
#include <GLFW/glfw3.h>
#include "../Header/Collision.h"

void processInput(GLFWwindow* window,
    float& uX, float& uY, float& uRot,
    float& distanceMoved);
bool processClick(GLFWwindow* window, float alienX, float alienY, float verticesAlien[16]);
#pragma once
