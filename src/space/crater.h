#ifndef CRATER_H
#define CRATER_H

#include "../geometry/coords.h"
#include "../geometry/couleur.h"
#include "../others/svgfile.h"
#include "../others/util.h"
#include "math.h"
#include <iostream>
#include <vector>

class Crater
{
    public:
        Crater(Coords position, int radius, Color color);
        Crater(Coords position, int radius);
        ~Crater();

        bool isOverlaping(std::vector<Crater> craters);
        void draw(Svgfile& out, void* clipPathID);

        void print();

    private:
        Coords m_position;
        int m_radius;
        Color m_color;
};

#endif // CRATER_H
