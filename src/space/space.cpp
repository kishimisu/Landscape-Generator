#include "space.h"

Space::Space(Settings settings)
{
    m_settings = settings;
    m_seed = settings.seeds[SpaceSeed];
    generatePlanets();
}

Space::~Space()
{
    //dtor
}

/// generate all the planets
void Space::generatePlanets()
{
    for(int i = 0; i < util::randomBetween(m_settings.planet_density, m_seed); i++)
    {
        Coords position;

        double x = util::random(0, SCENE_WIDTH, m_seed);
        double y = util::random(0, SCENE_HEIGHT, m_seed);
        double radius = util::randomBetween(m_settings.planet_size, m_seed);

        position.set(x, y);

        m_planets.push_back(Planet(position, radius, Color(true, m_seed), m_seed));
    }
}

/// draw the space
void Space::draw(Svgfile& out)
{
    for(unsigned int i = 0; i < m_planets.size(); i++)
        m_planets[i].draw(out, m_seed);
}
