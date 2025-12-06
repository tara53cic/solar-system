#include "../Header/Collision.h"

static BoundingBox g_planetBoxes[10];
static int g_planetCount = 0;


BoundingBox getBounds(float* vertices)
{
    BoundingBox box;

    box.left = vertices[0];  // top-left X
    box.top = vertices[1];  // top-left Y
    box.bottom = vertices[5];  // bottom-left Y
    box.right = vertices[8];  // bottom-right X

    return box;
}

void registerPlanetBox(const BoundingBox& box)
{
    if (g_planetCount < 10)
        g_planetBoxes[g_planetCount++] = box;
}


int checkPlanetHit(
    float rocketLeft, float rocketRight,
    float rocketTop, float rocketBottom
)
{
    for (int i = 0; i < g_planetCount; i++)
    {
        const BoundingBox& p = g_planetBoxes[i];

        if (!(rocketRight < p.left ||
            rocketLeft  > p.right ||
            rocketTop   < p.bottom ||
            rocketBottom > p.top))
        {
            return i + 1; 
        }
    }

    return 0; 
}
