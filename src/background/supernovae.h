#ifndef SUPERNOVAE_H
#define SUPERNOVAE_H

#include "../others/svgfile.h"
#include "../geometry/couleur.h"
#include "../geometry/gradient.h"
#include "../geometry/circle.h"
#include <random>

class Supernovae : public Circle
{
    public:
        using Circle::Circle;
        ~Supernovae();

        void draw(Svgfile& out, std::mt19937& seed);

    private:
};

#endif // SUPERNOVAE_H
