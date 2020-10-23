#ifndef GRADIENT_H
#define GRADIENT_H

#include "couleur.h"

struct Gradient
{
    double cx, cy, r, fx, fy;
    double offset[2];
    Color color[2];
    void* id;
};

struct Rotation
{
    double angle;
    double x, y;
};

#endif // GRADIENT_H
