#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "../geometry/coords.h"
#include "../others/svgfile.h"
#include "reactor.h"
#include <vector>
#include <random>

class FlyingObject
{
    public:
        FlyingObject(Coords position, double scale, Rotation rotation, int type, std::mt19937& seed);
        ~FlyingObject();

        void setupReactor();

        void draw(Svgfile& out);

    protected:
        int m_type;
        Coords m_position;
        double m_scale;
        Rotation m_rotation;
        std::vector<Reactor> m_reactors;
        std::mt19937 m_seed;
};

#endif // FLYINGOBJECT_H
