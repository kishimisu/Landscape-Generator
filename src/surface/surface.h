#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include <algorithm>
#include "math.h"
#include "mountain.h"
#include "../geometry/coords.h"
#include "../geometry/couleur.h"
#include "../others/svgfile.h"
#include "../others/util.h"
#include "tree.h"
#include "../others/settings.h"
#include <random>

class Surface
{
    public:
        Surface(){};
        Surface(Settings settings);
        ~Surface();

        void generateMountains();
        void generateTrees();
        Color randomTreeColor(int colorSet, Color base_color);

        void draw(Svgfile& out, void* gradientID);

    private:
        std::vector<Tree> m_trees;
        std::vector<Mountain> m_moutains;
        Coords m_position;
        double m_radius;
        Color m_color;
        Settings m_settings;
        std::mt19937 m_seed;
};

#endif // SURFACE_H
