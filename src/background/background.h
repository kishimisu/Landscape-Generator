#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <vector>
#include "star.h"
#include "supernovae.h"
#include "../others/util.h"
#include "../others/svgfile.h"
#include "blackhole.h"
#include "../others/settings.h"
#include <random>

class Background
{
    public:
        Background(){};
        Background(Settings settings);
        ~Background();

        void generateStars();
        void addStar(double x, double y, double radius);
        void addSupernovae();
        void generateBlackHoles();

        void draw(Svgfile& out);

    private:
        std::vector<Star> m_stars;
        std::vector<Supernovae> m_supernovaes;
        std::vector<BlackHole> m_blackHoles;
        Color m_color;
        Settings m_settings;
        std::mt19937 m_seed;
};

#endif // BACKGROUND_H
