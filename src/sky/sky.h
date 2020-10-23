#ifndef SKY_H
#define SKY_H

#include "flyingobject.h"
#include "../others/svgfile.h"
#include "../others/settings.h"
#include <random>

class Sky
{
    public:
        Sky(){};
        Sky(Settings settings);
        ~Sky();

        void generateSatellites();
        void generateSpaceships();

        void draw(Svgfile& out);

    private:
        std::vector<FlyingObject> m_satellites;
        std::vector<FlyingObject> m_spaceships;
        Settings m_settings;
        std::mt19937 m_seed;
};

#endif // SKY_H
