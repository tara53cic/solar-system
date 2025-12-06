#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Header/Util.h"
#include "../Header/TextRenderer.h"

#include <sstream>   
#include <iomanip>   
#include <cmath>

// Main fajl funkcija sa osnovnim komponentama OpenGL programa

//dodatak- pomoćna funkcija za određivanje bounding box-a objekta iz vertexa
struct BoundingBox {
    float left, right, top, bottom;
};

BoundingBox getBounds(float* vertices) {
    BoundingBox box;
    box.left = vertices[0];  // top-left X
    box.top = vertices[1];  // top-left Y
    box.bottom = vertices[5];  // bottom-left Y
    box.right = vertices[8];  // bottom-right X
    return box;
}


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

void formVAOs(float* verticesBackground, size_t rectSize, unsigned int& VAOrect,
    float* verticesNametag, size_t nametagSize, unsigned int& VAOnametag,
    float* verticesdistanceBackground, size_t distanceBackgroundSize, unsigned int& VAOdistanceBackground,
    float* verticesRocket, size_t rocketSize, unsigned int& VAOrocket) {

    // Pozadina

    unsigned int VBOrect;
    glGenVertexArrays(1, &VAOrect);
    glGenBuffers(1, &VBOrect);

    glBindVertexArray(VAOrect);
    glBindBuffer(GL_ARRAY_BUFFER, VBOrect);
    glBufferData(GL_ARRAY_BUFFER, rectSize, verticesBackground, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);



    //Pločica sa imenom
    unsigned int VBOnametag;
    glGenVertexArrays(1, &VAOnametag);
    glGenBuffers(1, &VBOnametag);

    glBindVertexArray(VAOnametag);
    glBindBuffer(GL_ARRAY_BUFFER, VBOnametag);
    glBufferData(GL_ARRAY_BUFFER, nametagSize, verticesNametag, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Pozadina distance teksta
    unsigned int VBOdistanceBackground;
    glGenVertexArrays(1, &VAOdistanceBackground);
    glGenBuffers(1, &VBOdistanceBackground);

    glBindVertexArray(VAOdistanceBackground);
    glBindBuffer(GL_ARRAY_BUFFER, VBOdistanceBackground);
    glBufferData(GL_ARRAY_BUFFER, distanceBackgroundSize, verticesdistanceBackground, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Raketa
    unsigned int VBOrocket;
    glGenVertexArrays(1, &VAOrocket);
    glGenBuffers(1, &VBOrocket);

    glBindVertexArray(VAOrocket);
    glBindBuffer(GL_ARRAY_BUFFER, VBOrocket);
    glBufferData(GL_ARRAY_BUFFER, rocketSize, verticesRocket, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void drawBackground(unsigned int backgroundShader, unsigned int VAOrect, unsigned int backgroundTexture) {

    glUseProgram(backgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBindVertexArray(VAOrect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawNametag(unsigned int nametagShader, unsigned int VAOnametag) {

    glUseProgram(nametagShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, nametagTexture);

    glBindVertexArray(VAOnametag);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawDistanceBackground(unsigned int distanceBackgroundShader, unsigned int VAOdistanceBackground) {

    glUseProgram(distanceBackgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, distanceBackgroundTexture);

    glBindVertexArray(VAOdistanceBackground);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawRocket(unsigned int rocketShader, unsigned int VAOrocket) {
    glUseProgram(rocketShader);

    glUniform2f(glGetUniformLocation(rocketShader, "uPos"), uX, uY);
    glUniform1f(glGetUniformLocation(rocketShader, "uRot"), uRot);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rocketTexture);

    glBindVertexArray(VAOrocket);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
    //pozadina
    unsigned int backgroundShader = createShader("Shaders/background.vert", "Shaders/background.frag");
    glUseProgram(backgroundShader);
    glUniform1i(glGetUniformLocation(backgroundShader, "uTex0"), 0);

    //pločica sa imenom
    unsigned int nametagShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(nametagShader);
    glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);

    //pozadina distance teksta
    unsigned int distanceBackgroundShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(distanceBackgroundShader);
    glUniform1i(glGetUniformLocation(distanceBackgroundShader, "uTex0"), 0);

    //raketa
    unsigned int rocketShader = createShader("Shaders/rocket.vert", "Shaders/rocket.frag");
    glUseProgram(rocketShader);
    glUniform1i(glGetUniformLocation(rocketShader, "uTex0"), 0);



    ////////////
    //temena 
    // 
    //pozadina

    float verticesBackground[] = {
        //   X      Y      U     V
        -1.0f,  1.0f,   0.0f, 1.0f, // top-left
        -1.0f, -1.0f,   0.0f, 0.0f, // bottom-left
         1.0f, -1.0f,   1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,   1.0f, 1.0f  // top-right
    };

    //pločica sa imenom

    float verticesNametag[] = {
        //   X      Y      U     V
        -1.0f, -0.85f,   0.0f, 1.0f, // top-left
        -1.0f, -1.0f,   0.0f, 0.0f, // bottom-left
        -0.4f, -1.0f,   1.0f, 0.0f, // bottom-right
        -0.4f, -0.85f,   1.0f, 1.0f  // top-right
    };

    //pozadina za Distance tekst

    float verticesTopLeftRect[] = {
        //   X       Y      U     V
        -1.0f,  1.0f,    0.0f, 1.0f,  // top-left
        -1.0f,  0.85f,    0.0f, 0.0f,  // bottom-left
        -0.4f,  0.85f,    1.0f, 0.0f,  // bottom-right
        -0.4f,  1.0f,    1.0f, 1.0f   // top-right
    };
    //raketa
    float verticesRocket[] = {
        //   X           Y        U     V  
        -0.39157f,  0.209545f,  -0.0f,  1.0f,  // top-left
        -0.39157f,  0.026825f,  -0.0f, -0.0f,  // bottom-left
        -0.28313f,  0.026825f,   1.0f, 0.0f,  // bottom-right
        -0.28313f,  0.209545f,   1.0f,  1.0f   // top-right
    };
    //providne površine za planete
    float verticesMercury[] = {
        // X       Y       U     V
        -0.6813f, 0.3622f,  0.0f, 1.0f, // top-left
        -0.6813f, 0.2296f,  0.0f, 0.0f, // bottom-left
        -0.6024f, 0.2296f,  1.0f, 0.0f, // bottom-right
        -0.6024f, 0.3622f,  1.0f, 1.0f  // top-right
    };


    float verticesVenus[] = {
    -0.5422f, -0.1980f,  0.0f, 1.0f,
    -0.5422f, -0.3724f,  0.0f, 0.0f,
    -0.4398f, -0.3724f,  1.0f, 0.0f,
    -0.4398f, -0.1980f,  1.0f, 1.0f
    };


    float verticesEarth[] = {
    -0.4012f, 0.1633f, 0.0f, 1.0f,
    -0.4012f, 0.0f,    0.0f, 0.0f,
    -0.2795f, 0.0f,    1.0f, 0.0f,
    -0.2795f, 0.1633f, 1.0f, 1.0f
    };


    float verticesMars[] = {
    -0.3169f, -0.4867f, 0.0f, 1.0f,
    -0.3169f, -0.6153f, 0.0f, 0.0f,
    -0.2398f, -0.6153f, 1.0f, 0.0f,
    -0.2398f, -0.4867f, 1.0f, 1.0f
    };


    float verticesJupiter[] = {
    0.0353f, 0.0788f, 0.0f, 1.0f,
    0.0353f, -0.3421f, 0.0f, 0.0f,
    0.2832f, -0.3421f, 1.0f, 0.0f,
    0.2832f, 0.0788f,  1.0f, 1.0f
    };


    float verticesSaturn[] = {
    0.2555f, 0.6880f, 0.0f, 1.0f,
    0.2555f, 0.3183f, 0.0f, 0.0f,
    0.4758f, 0.3183f, 1.0f, 0.0f,
    0.4758f, 0.6880f, 1.0f, 1.0f
    };


    float verticesUranus[] = {
    0.4985f, -0.1806f, 0.0f, 1.0f,
    0.4985f, -0.4056f, 0.0f, 0.0f,
    0.6337f, -0.4056f, 1.0f, 0.0f,
    0.6337f, -0.1806f, 1.0f, 1.0f
    };


    float verticesNeptune[] = {
    0.6097f, -0.6107f, 0.0f, 1.0f,
    0.6097f, -0.8278f, 0.0f, 0.0f,
    0.7380f, -0.8278f, 1.0f, 0.0f,
    0.7380f, -0.6107f, 1.0f, 1.0f
    };


    float verticesPluto[] = {
    0.8308f, 0.0181f, 0.0f, 1.0f,
    0.8308f, -0.0724f, 0.0f, 0.0f,
    0.8825f, -0.0724f, 1.0f, 0.0f,
    0.8825f, 0.0181f, 1.0f, 1.0f
    };




    ////////////
    //promenljive
    float distanceMoved = 0.0f;

    ////////////
    //formiranje VAO
    unsigned int VAObackground;
    unsigned int VAOnametag;
    unsigned int VAOdistanceBackground;
    unsigned int VAOrocket;

    formVAOs(verticesBackground, sizeof(verticesBackground), VAObackground,
        verticesNametag, sizeof(verticesNametag), VAOnametag,
        verticesTopLeftRect, sizeof(verticesTopLeftRect), VAOdistanceBackground,
        verticesRocket, sizeof(verticesRocket), VAOrocket);

 

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

        //prozor se zatvara na ESC

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        //pomeranje rakete i računanje distance

        float BkmPerPixel = 0.15f / 227.0f; // milijarda km po pikselu
        //računamo dimenzije prozora u pikselima
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

        //računamo distancu u odnosu na pređene piksele
        float dxPixels = dx * 0.01f * (screenWidth / 2.0f);
        float dyPixels = dy * 0.01f * (screenHeight / 2.0f);

        float distancePixels = sqrt(dxPixels * dxPixels + dyPixels * dyPixels);

        distanceMoved += distancePixels * BkmPerPixel;

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

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        // Normalizacija da bi se pozicija izražena u pikselima namapirala na OpenGL-ov prozor sa opsegom (-1, 1)
        float xposNorm = (xpos / screenWidth) * 2 - 1;
        float yposNorm = -((ypos / screenHeight) * 2 - 1);

       
        BoundingBox mercuryBox = getBounds(verticesMercury);
        BoundingBox venusBox = getBounds(verticesVenus);
        BoundingBox earthBox = getBounds(verticesEarth);
        BoundingBox marsBox = getBounds(verticesMars);
        BoundingBox jupiterBox = getBounds(verticesJupiter);
        BoundingBox saturnBox = getBounds(verticesSaturn);
        BoundingBox uranusBox = getBounds(verticesUranus);
        BoundingBox neptuneBox = getBounds(verticesNeptune);
        BoundingBox plutoBox = getBounds(verticesPluto);


        // Mercury
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (!(rocketRight < mercuryBox.left ||
                rocketLeft > mercuryBox.right ||
                rocketTop < mercuryBox.bottom ||
                rocketBottom > mercuryBox.top))
            {
                state = 1; hit = true;
            }
            if (!(rocketRight < venusBox.left ||
                rocketLeft > venusBox.right ||
                rocketTop < venusBox.bottom ||
                rocketBottom > venusBox.top))
            {
                state = 2; hit = true;
            }
            if (!(rocketRight < earthBox.left ||
                rocketLeft > earthBox.right ||
                rocketTop < earthBox.bottom ||
                rocketBottom > earthBox.top))
            {
                state = 3; hit = true;
            }
            if (!(rocketRight < marsBox.left ||
                rocketLeft > marsBox.right ||
                rocketTop < marsBox.bottom ||
                rocketBottom > marsBox.top))
            {
                state = 4; hit = true;
            }
            if (!(rocketRight < jupiterBox.left ||
                rocketLeft > jupiterBox.right ||
                rocketTop < jupiterBox.bottom ||
                rocketBottom > jupiterBox.top))
            {
                state = 5; hit = true;
            }
            if (!(rocketRight < saturnBox.left ||
                rocketLeft > saturnBox.right ||
                rocketTop < saturnBox.bottom ||
                rocketBottom > saturnBox.top))
            {
                state = 6; hit = true;
            }
            if (!(rocketRight < uranusBox.left ||
                rocketLeft > uranusBox.right ||
                rocketTop < uranusBox.bottom ||
                rocketBottom > uranusBox.top))
            {
                state = 7; hit = true;
            }
            if (!(rocketRight < neptuneBox.left ||
                rocketLeft > neptuneBox.right ||
                rocketTop < neptuneBox.bottom ||
                rocketBottom > neptuneBox.top))
            {
                state = 8; hit = true;
            }
            if (!(rocketRight < plutoBox.left ||
                rocketLeft > plutoBox.right ||
                rocketTop < plutoBox.bottom ||
                rocketBottom > plutoBox.top))
            {
                state = 9; hit = true;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            state = 0;
        }

        /////////////////////


        //crtaj
        switch (state)
        {
        case 0:
        {
            drawBackground(backgroundShader, VAObackground,spaceTexture); // crta pozadinu
            drawDistanceBackground(distanceBackgroundShader, VAOdistanceBackground); // crta pozadinu distance teksta
            drawRocket(rocketShader, VAOrocket); // crta raketu
            textRenderer.RenderText(distText, 25.0f, mode->height - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)); // crta distance tekst
            break;
        }
        case 1: {
            drawBackground(backgroundShader, VAObackground, mercuryTexture); // crta pozadinu
            break;
        }
        default:
            drawBackground(backgroundShader, VAObackground, spaceTexture); // crta pozadinu
            drawDistanceBackground(distanceBackgroundShader, VAOdistanceBackground); // crta pozadinu distance teksta
            drawRocket(rocketShader, VAOrocket); // crta raketu
            textRenderer.RenderText(distText, 25.0f, mode->height - 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f)); // crta distance tekst
            break;
        }

        drawNametag(nametagShader, VAOnametag); // crta pločicu sa imenom
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