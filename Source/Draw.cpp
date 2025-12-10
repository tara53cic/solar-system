#include "../Header/Draw.h"         

void drawBackground(unsigned int backgroundShader, unsigned int VAOrect, unsigned int backgroundTexture) {

    glUseProgram(backgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBindVertexArray(VAOrect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawNametag(unsigned int nametagShader, unsigned int VAOnametag, unsigned int nametagTexture) {

    glUseProgram(nametagShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, nametagTexture);

    glBindVertexArray(VAOnametag);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawDistanceBackground(unsigned int distanceBackgroundShader, unsigned int VAOdistanceBackground, unsigned int distanceBackgroundTexture) {

    glUseProgram(distanceBackgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, distanceBackgroundTexture);

    glBindVertexArray(VAOdistanceBackground);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawRocket(unsigned int rocketShader, unsigned int VAOrocket, unsigned int rocketTexture, float uX, float uY, float uRot) {
    glUseProgram(rocketShader);

    glUniform2f(glGetUniformLocation(rocketShader, "uPos"), uX, uY);
    glUniform1f(glGetUniformLocation(rocketShader, "uRot"), uRot);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rocketTexture);

    glBindVertexArray(VAOrocket);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawAlienIcon(unsigned int alienIconShader, unsigned int VAOalienIcon, unsigned int alienIconTexture) {

    glUseProgram(alienIconShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, alienIconTexture);

    glBindVertexArray(VAOalienIcon);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

Vec2 drawAlien(unsigned int alienShader, unsigned int VAOalien, unsigned int alienTexture) {
    glUseProgram(alienShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, alienTexture);

    float speed = 0.3f;         
    float yPos = 0.0f;          
    float screenLeft = -1.0f;   
    float screenRight = 1.0f;   
    float width = 0.17f;        

    float xPos = fmod(glfwGetTime() * speed + screenRight, (screenRight - screenLeft + width)) + screenLeft - width;

    GLint loc = glGetUniformLocation(alienShader, "uPos");
    if (loc != -1) {
        glUniform2f(loc, xPos, yPos);
    }

    glBindVertexArray(VAOalien);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    return { xPos, yPos };
}
void drawHelp(unsigned int backgroundShader, unsigned int VAOrect, unsigned int backgroundTexture) {

    glUseProgram(backgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBindVertexArray(VAOrect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
