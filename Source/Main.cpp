#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Header/Util.h"
#include "../Header/TextRenderer.h"
#include "../Header/Vertices.h"
#include "../Header/VAOManager.h"
#include "../Header/Draw.h"
#include "../Header/Shaders.h"
#include "../Header/Input.h"
#include "../Header/Collision.h"

#include <sstream>   
#include <iomanip>   
#include <cmath>

// Main fajl funkcija sa osnovnim komponentama OpenGL programa


//promenljiva za praćenje scene
int state;

//promenljive za pomeranje rakete

float uX = 0.0f; 
float uY = -0.0f;

float uRot = 0.0f;

//promenljive za teksture
unsigned spaceTexture;
unsigned nametagTexture;
unsigned distanceBackgroundTexture;
unsigned rocketTexture;
unsigned mercuryTexture;

void preprocessTexture(unsigned& texture, const char* filepath) {
    texture = loadImageToTexture(filepath); // Učitavanje teksture
    glBindTexture(GL_TEXTURE_2D, texture); // Vezujemo se za teksturu kako bismo je podesili

    // Generisanje mipmapa - predefinisani različiti formati za lakše skaliranje po potrebi (npr. da postoji 32 x 32 verzija slike, ali i 16 x 16, 256 x 256...)
    glGenerateMipmap(GL_TEXTURE_2D);

    // Podešavanje strategija za wrap-ovanje - šta da radi kada se dimenzije teksture i poligona ne poklapaju
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S - tekseli po x-osi
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T - tekseli po y-osi

    // Podešavanje algoritma za smanjivanje i povećavanje rezolucije: nearest - bira najbliži piksel, linear - usrednjava okolne piksele
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //podešavanje prozora na fullscreen

    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(mon);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "RA 141/2022-2D projekat", mon, NULL);

    if (window == NULL) return endProgram("Prozor nije uspeo da se kreira.");
    glfwMakeContextCurrent(window);
    ///////////////////////////

    //učitavalje kursora
    GLFWcursor* cursor = loadImageToCursor("Resources/star.png");
    if (cursor) glfwSetCursor(window, cursor);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.8f, 0.6f, 1.0f);
    ////////////

    //podesavanje frejmova u sekundi
    const double frameTime = 1.0 / 75.0;
    double lastTime = glfwGetTime();
    ////////////////

    if (glewInit() != GLEW_OK) return endProgram("GLEW nije uspeo da se inicijalizuje.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ////////////
    //učitavanje fonta
    TextRenderer textRenderer(mode->width, mode->height);
    textRenderer.Load("Resources/ScienceGothic_Condensed-Regular.ttf", 38);

    /////////////////////


    //učitavanje teksture
    //pozadina
    preprocessTexture(spaceTexture, "Resources/-OWrBW3G.png");
    //pločica sa imenom
    preprocessTexture(nametagTexture, "Resources/purpletransparent50.png");
    //pozadina distance teksta
    preprocessTexture(distanceBackgroundTexture, "Resources/purpletransparent50.png");
    //raketa
    preprocessTexture(rocketTexture, "Resources/rocket2.png");
    //merkur pozadina
    preprocessTexture(mercuryTexture, "Resources/Screenshot_20190320-145515.png");
    //////////
    //učitavanje shadera
    unsigned int backgroundShader, nametagShader, distanceBackgroundShader, rocketShader;
    loadAllShaders(backgroundShader, nametagShader, distanceBackgroundShader, rocketShader);

    ////////////
    
    ////////////
    //promenljive
    float distanceMoved = 0.0f;

    ////////////
    //formiranje VAO
    unsigned int VAObackground;
    unsigned int VAOnametag;
    unsigned int VAOdistanceBackground;
    unsigned int VAOrocket;

    formVAOs(
        verticesBackground, sizeof(verticesBackground), VAObackground,
        verticesNametag, sizeof(verticesNametag), VAOnametag,
        verticesTopLeftRect, sizeof(verticesTopLeftRect), VAOdistanceBackground,
        verticesRocket, sizeof(verticesRocket), VAOrocket
    );

 

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        // Ograničavanje broja frejmova u sekundi na 75 FPS
        double current = glfwGetTime();
        double dt = current - lastTime;

        if (dt < frameTime) {
            double wait = frameTime - dt;
            while (glfwGetTime() - current < wait) {}
        }
        lastTime = glfwGetTime();

        //////////////////////
        //akcije sa tastature

        processInput(window, uX, uY, uRot, distanceMoved);


        //priprema teksta za distancu
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << distanceMoved;
        std::string distText = "Distance: " + ss.str() + " billions of km";

        //////////////////////////

        //prilagođena pozicija rakete za detekciju sudara

        float rocketCenterX = uX + (-0.33735f); 
        float rocketCenterY = uY + (0.118185f);

        float rocketHalfX = 0.05422f;
        float rocketHalfY = 0.09136f;

        float rocketLeft = rocketCenterX - rocketHalfX;
        float rocketRight = rocketCenterX + rocketHalfX;
        float rocketTop = rocketCenterY + rocketHalfY;
        float rocketBottom = rocketCenterY - rocketHalfY;


        //jesmo li na planeti?

        bool hit = false;

        registerPlanetBox(getBounds(verticesMercury));
        registerPlanetBox(getBounds(verticesVenus));
        registerPlanetBox(getBounds(verticesEarth));
        registerPlanetBox(getBounds(verticesMars));
        registerPlanetBox(getBounds(verticesJupiter));
        registerPlanetBox(getBounds(verticesSaturn));
        registerPlanetBox(getBounds(verticesUranus));
        registerPlanetBox(getBounds(verticesNeptune));
        registerPlanetBox(getBounds(verticesPluto));

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            state = checkPlanetHit(rocketLeft, rocketRight, rocketTop, rocketBottom);
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            state = 0;
        }

        //crtaj u zavisnosti od stanja
        switch (state)
        {
        case 0:
        {
            drawBackground(backgroundShader, VAObackground,spaceTexture); // crta pozadinu
            drawDistanceBackground(distanceBackgroundShader, VAOdistanceBackground, distanceBackgroundTexture); // crta pozadinu distance teksta
            drawRocket(rocketShader, VAOrocket, rocketTexture, uX, uY,uRot); // crta raketu
            textRenderer.RenderText(distText, 25.0f, mode->height - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)); // crta distance tekst
            break;
        }
        case 1: {
            drawBackground(backgroundShader, VAObackground, mercuryTexture); // crta pozadinu
            break;
        }
        default:
            drawBackground(backgroundShader, VAObackground, spaceTexture); // crta pozadinu
            drawDistanceBackground(distanceBackgroundShader, VAOdistanceBackground, distanceBackgroundTexture); // crta pozadinu distance teksta
            drawRocket(rocketShader, VAOrocket, rocketTexture, uX, uY, uRot); // crta raketu
            textRenderer.RenderText(distText, 25.0f, mode->height - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)); // crta distance tekst
            break;
        }

        drawNametag(nametagShader, VAOnametag, distanceBackgroundTexture); // crta pločicu sa imenom
        std::string nametagText = "Tara Petricic, RA 141/2022";
        textRenderer.RenderText(nametagText, 25.0f, 28.0f, 1.0f, glm::vec3(1.0f));
        ///////////////////////////


        glfwSwapBuffers(window);
        glfwPollEvents();

        //forsiraj kursor da se učita

        static bool cursorFixed = false;
        if (!cursorFixed) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursor(window, cursor);
            cursorFixed = true;
        }

    }
    glDeleteProgram(backgroundShader);
    glDeleteProgram(nametagShader);
    glDeleteProgram(distanceBackgroundShader);
    glDeleteProgram(rocketShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}