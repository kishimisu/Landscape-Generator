#ifndef CIRCLE_H
#define CIRCLE_H

#include "coords.h"
#include "couleur.h"
#include "../others/svgfile.h"

class Circle
{
    public:
        Circle(){};
        Circle(Coords position, double radius, Color color);
        Circle(Coords position, Rotation rotation, double radius, Color color);
        ~Circle();

    void drawCircle(Svgfile& out);

    protected:
        Coords m_position;
        Rotation m_rotation;
        double m_radius;
        Color m_color;
};

#endif // CIRCLE_H
