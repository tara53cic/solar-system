#include "../Header/Vertices.h"

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

//plo?ica sa imenom

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

float verticesPlutoIcon[] = {
    //   X      Y      U     V
     0.93f, 1.00f,   0.0f, 1.0f,   // top-left
     0.93f, 0.88f,   0.0f, 0.0f,   // bottom-left
     1.0f, 0.88f,   1.0f, 0.0f,   // bottom-right
     1.0f, 1.00,   1.0f, 1.0f    // top-right
};

float verticesNeptuneIcon[] = {
	//   X      Y      U     V
	 0.86f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.86f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.93f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.93f, 1.00f,   1.0f, 1.0f    // top-right
};

float verticesUranusIcon[] = {
	//   X      Y      U     V
	 0.79f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.79f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.86f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.86f, 1.00f,   1.0f, 1.0f    // top-right
};
float verticesSaturnIcon[] = {
	//   X      Y      U     V
	 0.72f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.72f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.79f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.79f, 1.00f,   1.0f, 1.0f    // top-right
};
float verticesJupiterIcon[] = {
	//   X      Y      U     V
	 0.65f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.65f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.72f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.72f, 1.00f,   1.0f, 1.0f    // top-right
};
float verticesMarsIcon[] = {
	//   X      Y      U     V
	 0.57f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.57f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.65f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.65f, 1.00f,   1.0f, 1.0f    // top-right
};
float verticesVenusIcon[] = {
	//   X      Y      U     V
	 0.50f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.50f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.57f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.57f, 1.00f,   1.0f, 1.0f    // top-right
};
float verticesMercuryIcon[] = {
	//   X      Y      U     V
	 0.43f, 1.00f,   0.0f, 1.0f,   // top-left
	 0.43f, 0.88f,   0.0f, 0.0f,   // bottom-left
	 0.50f, 0.88f,   1.0f, 0.0f,   // bottom-right
	 0.50f, 1.00f,   1.0f, 1.0f    // top-right
};

float verticesAlien[] = {
    //   X       Y       U   V
    -0.08125f,  -0.6078f, 0.0f, 1.0f, // top-left
    -0.08125f, -0.9411f, 0.0f, 0.0f, // bottom-left
     0.08125f, -0.9411f, 1.0f, 0.0f, // bottom-right
     0.08125f,  -0.6078f, 1.0f, 1.0f  // top-right
};



