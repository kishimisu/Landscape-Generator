#ifndef TREE_H
#define TREE_H

#include <vector>
#include <math.h>
#include "../geometry/polygon.h"
#include "../others/svgfile.h"
#include "../geometry/couleur.h"
#include <random>

class Tree
{
    public:
        Tree(std::vector<Polygon> segments, Coords position, double surfaceHeight, double width, Rotation rotation, double blur, Color color, std::mt19937& seed);
        ~Tree();

        void print();

        void draw(Svgfile& out);
        void drawTreeShadow(Svgfile& out);
        void drawSegmentShadow(Polygon& segment, Svgfile& out);
        void drawTrunkShadow(Polygon& trunk, Svgfile& out);

        bool operator<(Tree const& tree) const { return m_surfaceHeight > tree.m_surfaceHeight; };

    private:
        std::vector<Polygon> m_segments;
        Color m_color;
        double m_surfaceHeight;
        double m_width;
        Rotation m_rotation;
        Coords m_position;
        double m_blur;
        std::mt19937 m_seed;
};

#endif // TREE_H
