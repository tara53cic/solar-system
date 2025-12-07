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

//uhvaćen vanzemaljac?

bool mercuryCaught = false;
bool venusCaught = false;
bool marsCaught = false;
bool jupiterCaught = false;
bool saturnCaught = false;
bool uranusCaught = false;
bool neptuneCaught = false;
bool plutoCaught = false;

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
unsigned venusTexture;
unsigned marsTexture;
unsigned jupiterTexture;
unsigned saturnTexture;
unsigned uranusTexture;
unsigned neptuneTexture;
unsigned plutoTexture;

unsigned mercuryAlienTexture;
unsigned venusAlienTexture;
unsigned marsAlienTexture;
unsigned jupiterAlienTexture;
unsigned saturnAlienTexture;
unsigned uranusAlienTexture;
unsigned neptuneAlienTexture;
unsigned plutoAlienTexture;

unsigned mercuryAlienCaughtTexture;
unsigned mercuryAlienNotCaughtTexture;
unsigned venusAlienNotCaughtTexture;
unsigned venusAlienCaughtTexture;
unsigned marsAlienNotCaughtTexture;
unsigned marsAlienCaughtTexture;
unsigned jupiterAlienNotCaughtTexture;
unsigned jupiterAlienCaughtTexture;
unsigned saturnAlienNotCaughtTexture;
unsigned saturnAlienCaughtTexture;
unsigned uranusAlienNotCaughtTexture;
unsigned uranusAlienCaughtTexture;
unsigned neptuneAlienNotCaughtTexture;
unsigned neptuneAlienCaughtTexture;
unsigned plutoAlienNotCaughtTexture;
unsigned plutoAlienCaughtTexture;

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
    //planete-pozadine
    preprocessTexture(mercuryTexture, "Resources/Screenshot_20190320-145515.png");
    preprocessTexture(venusTexture, "Resources/phoebe-regio-640x381-ezgif.com-webp-to-jpg-converter.jpg");
    preprocessTexture(marsTexture, "Resources/istockphoto-1353996708-612x612.jpg");
    preprocessTexture(jupiterTexture, "jup.jpg");
    preprocessTexture(saturnTexture, "Resources/PIA17043.jpg");
    preprocessTexture(uranusTexture, "Resources/61HS9YSFT4L._AC_UF894,1000_QL80_.jpg");
    preprocessTexture(neptuneTexture, "Resources/images.jpg");
    preprocessTexture(plutoTexture, "Resources/neptune_fin_flood_LD_v4.jpg");
    //planete-vanzemaljci
    preprocessTexture(mercuryAlienTexture, "Resources/alien1_1.png");
    preprocessTexture(venusAlienTexture, "Resources/alien2_1.png");
    preprocessTexture(marsAlienTexture, "Resources/alien3_1.png");
    preprocessTexture(jupiterAlienTexture, "Resources/alien4_1.png");
    preprocessTexture(saturnAlienTexture, "Resources/alien5_1.png");
    preprocessTexture(uranusAlienTexture, "Resources/alien6_1.png");
    preprocessTexture(neptuneAlienTexture, "Resources/alien7_1.png");
    preprocessTexture(plutoAlienTexture, "Resources/alien8_1.png");
    //uhvaćeni vanzemaljci
    preprocessTexture(mercuryAlienCaughtTexture, "Resources/captured1.png");
    preprocessTexture(venusAlienCaughtTexture, "Resources/captured2.png");
    preprocessTexture(marsAlienCaughtTexture, "Resources/captured3.png");
    preprocessTexture(jupiterAlienCaughtTexture, "Resources/captured4.png");
    preprocessTexture(saturnAlienCaughtTexture, "Resources/captured5.png");
    preprocessTexture(uranusAlienCaughtTexture, "Resources/captured6.png");
    preprocessTexture(neptuneAlienCaughtTexture, "Resources/captured7.png");
    preprocessTexture(plutoAlienCaughtTexture, "Resources/captured8.png");

    //neuhvaćeni vanzemaljci
    preprocessTexture(mercuryAlienNotCaughtTexture, "Resources/uncaptured1.png");
    preprocessTexture(venusAlienNotCaughtTexture, "Resources/uncaptured2.png");
    preprocessTexture(marsAlienNotCaughtTexture, "Resources/uncaptured3.png");
    preprocessTexture(jupiterAlienNotCaughtTexture, "Resources/uncaptured4.png");
    preprocessTexture(saturnAlienNotCaughtTexture, "Resources/uncaptured5.png");
    preprocessTexture(uranusAlienNotCaughtTexture, "Resources/uncaptured6.png");
    preprocessTexture(neptuneAlienNotCaughtTexture, "Resources/uncaptured7.png");
    preprocessTexture(plutoAlienNotCaughtTexture, "Resources/uncaptured8.png");
    //////////
    //učitavanje shadera
    unsigned int backgroundShader, nametagShader, distanceBackgroundShader, rocketShader, alienIconShader, alienShader;
    loadAllShaders(backgroundShader, nametagShader, distanceBackgroundShader, rocketShader,alienIconShader,alienShader);

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
    unsigned int VAOplutoIcon;
    unsigned int VAOmercuryIcon;
    unsigned int VAOvenusIcon;
    unsigned int VAOmarsIcon;
    unsigned int VAOjupiterIcon;
    unsigned int VAOsaturnIcon;
    unsigned int VAOuranusIcon;
    unsigned int VAOneptuneIcon;
    unsigned int VAOAlien;
    

    formVAOs(
        verticesBackground, sizeof(verticesBackground), VAObackground,
        verticesNametag, sizeof(verticesNametag), VAOnametag,
        verticesTopLeftRect, sizeof(verticesTopLeftRect), VAOdistanceBackground,
        verticesRocket, sizeof(verticesRocket), VAOrocket,
        verticesPlutoIcon, sizeof(verticesPlutoIcon), VAOplutoIcon,
        verticesMercuryIcon, sizeof(verticesMercuryIcon), VAOmercuryIcon,
        verticesVenusIcon, sizeof(verticesVenusIcon), VAOvenusIcon,
        verticesMarsIcon, sizeof(verticesMarsIcon), VAOmarsIcon,
        verticesJupiterIcon, sizeof(verticesJupiterIcon), VAOjupiterIcon,
        verticesSaturnIcon, sizeof(verticesSaturnIcon), VAOsaturnIcon,
        verticesUranusIcon, sizeof(verticesUranusIcon), VAOuranusIcon,
        verticesNeptuneIcon, sizeof(verticesNeptuneIcon), VAOneptuneIcon,
        verticesAlien, sizeof(verticesAlien),VAOAlien
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
            drawBackground(backgroundShader, VAObackground, spaceTexture); // crta pozadinu
            drawDistanceBackground(distanceBackgroundShader, VAOdistanceBackground, distanceBackgroundTexture); // crta pozadinu distance teksta
            drawRocket(rocketShader, VAOrocket, rocketTexture, uX, uY, uRot); // crta raketu
            textRenderer.RenderText(distText, 25.0f, mode->height - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)); // crta distance tekst
            break;
        }
        case 1: 
        {
            drawBackground(backgroundShader, VAObackground, mercuryTexture); // crta pozadinu
            if (!mercuryCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, mercuryAlienTexture);
                mercuryCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }
        case 2: {
            drawBackground(backgroundShader, VAObackground, venusTexture); // crta pozadinu
            if (!venusCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, venusAlienTexture);
                venusCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }
        case 3: {
            drawBackground(backgroundShader, VAObackground, marsTexture); // crta pozadinu
            if (!marsCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, marsAlienTexture);
                marsCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }
        case 4: {
            drawBackground(backgroundShader, VAObackground, jupiterTexture); // crta pozadinu
            if (!jupiterCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, jupiterAlienTexture);
                jupiterCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }
        case 5: {
            drawBackground(backgroundShader, VAObackground, saturnTexture); // crta pozadinu
            if (!saturnCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, saturnAlienTexture);
                saturnCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }
        case 6:
        {
            drawBackground(backgroundShader, VAObackground, uranusTexture); // crta pozadinu
            if (!uranusCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, uranusAlienTexture);
                uranusCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }
        case 7:
        {
            drawBackground(backgroundShader, VAObackground, neptuneTexture); // crta pozadinu
            if (!neptuneCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, neptuneAlienTexture);
                neptuneCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }

        case 8:
        {
            drawBackground(backgroundShader, VAObackground, plutoTexture); // crta pozadinu
            if (!plutoCaught) {
                Vec2 alienPos = drawAlien(alienShader, VAOAlien, plutoAlienTexture);
                plutoCaught = processClick(window, alienPos.x, alienPos.y, verticesAlien);
            }
            break;
        }

        default:
        {
            drawBackground(backgroundShader, VAObackground, spaceTexture); // crta pozadinu
            drawDistanceBackground(distanceBackgroundShader, VAOdistanceBackground, distanceBackgroundTexture); // crta pozadinu distance teksta
            drawRocket(rocketShader, VAOrocket, rocketTexture, uX, uY, uRot); // crta raketu
            textRenderer.RenderText(distText, 25.0f, mode->height - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)); // crta distance tekst
            break;
        }
        }
        drawNametag(nametagShader, VAOnametag, distanceBackgroundTexture); // crta pločicu sa imenom
        std::string nametagText = "Tara Petricic, RA 141/2022";
        textRenderer.RenderText(nametagText, 25.0f, 28.0f, 1.0f, glm::vec3(1.0f));


        //crta ikonice vanzemaljaca
        if (!plutoCaught) {
            drawAlienIcon(alienIconShader, VAOplutoIcon, plutoAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOplutoIcon, plutoAlienCaughtTexture);
        }

        if (!mercuryCaught) {
            drawAlienIcon(alienIconShader, VAOmercuryIcon, mercuryAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOmercuryIcon, mercuryAlienCaughtTexture);
        }

        if (!venusCaught) {
            drawAlienIcon(alienIconShader, VAOvenusIcon, venusAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOvenusIcon, venusAlienCaughtTexture);
        }

        if (!marsCaught) {
            drawAlienIcon(alienIconShader, VAOmarsIcon, marsAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOmarsIcon, marsAlienCaughtTexture);
        }

        if (!jupiterCaught) {
            drawAlienIcon(alienIconShader, VAOjupiterIcon, jupiterAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOjupiterIcon, jupiterAlienCaughtTexture);
        }

        if (!saturnCaught) {
            drawAlienIcon(alienIconShader, VAOsaturnIcon, saturnAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOsaturnIcon, saturnAlienCaughtTexture);
        }

        if (!uranusCaught) {
            drawAlienIcon(alienIconShader, VAOuranusIcon, uranusAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOuranusIcon, uranusAlienCaughtTexture);
        }

        if (!neptuneCaught) {
            drawAlienIcon(alienIconShader, VAOneptuneIcon, neptuneAlienNotCaughtTexture);
        }
        else {
            drawAlienIcon(alienIconShader, VAOneptuneIcon, neptuneAlienCaughtTexture);
        }

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