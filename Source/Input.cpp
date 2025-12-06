#include "../Header/Input.h"
#include <GLFW/glfw3.h>
#include <cmath>

void processInput(
    GLFWwindow* window,
    float& uX, float& uY, float& uRot,
    float& distanceMoved
)
{
    //prozor se zatvara na esc
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //pomeranje rakete i ra?unanje distance

    float BkmPerPixel = 0.15f / 227.0f; // milijarda km po pikselu
    //ra?unamo dimenzije prozora u pikselima
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    float dx = 0, dy = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dy += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dy -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dx += 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dx -= 1;

    // pomeramo raketu
    uX += dx * 0.01f;
    uY += dy * 0.01f;

    // rotiramo raketu
    if (dx != 0 || dy != 0) {
        uRot = atan2(dx, dy);
    }

    //ra?unamo distancu u odnosu na pre?ene piksele
    float dxPixels = dx * 0.01f * (screenWidth / 2.0f);
    float dyPixels = dy * 0.01f * (screenHeight / 2.0f);

    float distancePixels = sqrt(dxPixels * dxPixels + dyPixels * dyPixels);

    distanceMoved += distancePixels * BkmPerPixel;
}