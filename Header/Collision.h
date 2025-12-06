#pragma once

struct BoundingBox {
    float left, right, top, bottom;
};

BoundingBox getBounds(float* vertices);


void registerPlanetBox(const BoundingBox& box);

int checkPlanetHit(
    float rocketLeft, float rocketRight,
    float rocketTop, float rocketBottom
);

