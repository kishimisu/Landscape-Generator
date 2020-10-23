#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "../geometry/circle.h"
#include "../others/svgfile.h"
#include <math.h>
#include <random>

class BlackHole : public Circle
{
    public:
        BlackHole(Coords position, Color color, double radius);
        ~BlackHole();

        void draw(Svgfile& out, std::mt19937& seed);
};

#endif // BLACKHOLE_H
