#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include "couleur.h"
#include "../others/svgfile.h"

class Svgfile;

enum FlipAnchor { FromLeft, FromRight, FromMiddle };

class Polygon
{
    public:
        Polygon(std::vector<Coords> points, Color color, double blur);
        Polygon(Color color, Rotation rotation, double blur);
        Polygon();
        ~Polygon();

        void addPoint(Coords position);
        void translate(Coords translation);
        void flipVertically(FlipAnchor anchor);

        std::vector<Coords> getPoints();

        void drawPolygon(Svgfile& out);

    protected:
        std::vector<Coords> m_points;
        Color m_color;
        Rotation m_rotation;
        double m_blur = 0.0;
};

#endif // POLYGON_H
