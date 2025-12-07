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
bool processClick(GLFWwindow* window, float alienX, float alienY, float verticesAlien[16]) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

        float xposNorm = (xpos / screenWidth) * 2 - 1;
        float yposNorm = -((ypos / screenHeight) * 2 - 1);

        BoundingBox box = getAlienBounds(verticesAlien, alienX, alienY);

        if (xposNorm >= box.left && xposNorm <= box.right &&
            yposNorm >= box.bottom && yposNorm <= box.top)
        {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                return true;
            }
		}
		else {
			return false;
        }


}