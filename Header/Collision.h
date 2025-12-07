#pragma once

struct BoundingBox {
    float left, right, top, bottom;
};

BoundingBox getBounds(float* vertices);

BoundingBox getAlienBounds(float* vertices, float posX, float posY);


void registerPlanetBox(const BoundingBox& box);

int checkPlanetHit(
    float rocketLeft, float rocketRight,
    float rocketTop, float rocketBottom
);

