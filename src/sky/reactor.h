#ifndef REACTOR_H
#define REACTOR_H

#include "../geometry/coords.h"
#include "../others/svgfile.h"

enum TypeFlame
{
    BigFlame, SmallFlame
};

class Reactor
{
    public:
        Reactor(){};
        Reactor(Coords position, double scale, Rotation rotation, int type);
        ~Reactor();

        void draw(Svgfile& out);

    private:
        Coords m_position;
        double m_scale;
        Rotation m_rotation;
        int m_type;
};

#endif // REACTOR_H
