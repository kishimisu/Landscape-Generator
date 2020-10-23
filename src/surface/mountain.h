#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "../geometry/couleur.h"
#include "../geometry/polygon.h"
#include "../others/svgfile.h"
#include <random>

class Mountain : public Polygon
{
    public:
        Mountain(std::vector<Coords> points, Color color, double height, double blur);
        Mountain(Color color, double height);
        ~Mountain();

    void draw(Svgfile& out, std::mt19937& seed);
    void drawSnow(Svgfile& out, std::mt19937& seed);
    void drawShadow(Svgfile& out);

    private:
        double m_height;
};

#endif // MOUNTAIN_H
