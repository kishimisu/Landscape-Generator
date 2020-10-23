#ifndef STAR_H
#define STAR_H

#include "../geometry/couleur.h"
#include "../geometry/coords.h"
#include "../others/svgfile.h"
#include "../geometry/circle.h"

class Star : public Circle
{
    public:
        using Circle::Circle;
        ~Star();

        void draw(Svgfile& out);

    private:
};

#endif // STAR_H
