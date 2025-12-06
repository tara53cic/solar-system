#include "../Header/Shaders.h"
#include "../Header/Util.h"
#include <GL/glew.h>

unsigned int loadAllShaders(
    unsigned int& backgroundShader,
    unsigned int& nametagShader,
    unsigned int& distanceBackgroundShader,
    unsigned int& rocketShader)
{
    backgroundShader = createShader("Shaders/background.vert", "Shaders/background.frag");
    glUseProgram(backgroundShader);
    glUniform1i(glGetUniformLocation(backgroundShader, "uTex0"), 0);

    nametagShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(nametagShader);
    glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);

    distanceBackgroundShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(distanceBackgroundShader);
    glUniform1i(glGetUniformLocation(distanceBackgroundShader, "uTex0"), 0);

    rocketShader = createShader("Shaders/rocket.vert", "Shaders/rocket.frag");
    glUseProgram(rocketShader);
    glUniform1i(glGetUniformLocation(rocketShader, "uTex0"), 0);

    return 1;
}