#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "../space/planet.h"
#include "../space/space.h"
#include "util.h"
#include "svgfile.h"
#include "../surface/surface.h"
#include "../sky/sky.h"
#include "../background/background.h"
#include "settings.h"

class Scene
{
    public:
        Scene(Settings settings);
        ~Scene();

        void draw(Svgfile& out);

    private:
        Background m_background;
        Space m_space;
        Sky m_sky;
        Surface m_surface;
        Settings m_settings;
};

#endif // SCENE_H
