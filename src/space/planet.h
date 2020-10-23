#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <vector>
#include <math.h>
#include "../geometry/coords.h"
#include "crater.h"
#include "../others/util.h"
#include "../geometry/couleur.h"
#include "../others/settings.h"

class Planet
{
    public:
        Planet(Coords position, double radius, Color color, std::mt19937& seed);
        ~Planet();

        void addCratersStyle_1(std::mt19937& seed);
        void addCratersStyle_2_3(bool shade, std::mt19937& seed);
        void draw(Svgfile& out, std::mt19937& seed);
        void drawShadow(Svgfile& out, std::mt19937& seed);
        void drawRing(Svgfile& out, bool frontRing, Color top, Color bottom, double ry, double radius, double strokeWidth, Rotation rotation);

        void print();

    private:
        Color m_color;
        double m_radius;
        Coords m_position;
        std::vector<Crater> m_craters;
};

#endif // PLANET_H
