#include "../Header/VAOManager.h"


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



    //Plo?ica sa imenom
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