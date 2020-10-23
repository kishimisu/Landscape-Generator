#ifndef SPACE_H
#define SPACE_H

#include <iostream>
#include <vector>
#include "../others/util.h"
#include "../others/svgfile.h"
#include "planet.h"
#include "../others/settings.h"

class Space
{
    public:
        Space(){};
        Space(Settings settings);
        ~Space();

        void generatePlanets();

        void draw(Svgfile& out);

    private:
        std::vector<Planet> m_planets;
        Settings m_settings;
        std::mt19937 m_seed;
};

#endif // SPACE_H
