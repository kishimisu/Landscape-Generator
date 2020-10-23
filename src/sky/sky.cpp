#include "sky.h"

Sky::Sky(Settings settings)
{
    m_settings = settings;
    m_seed = settings.seeds[SkySeed];

    generateSpaceships();
    generateSatellites();
}

Sky::~Sky()
{
    //dtor
}

void Sky::generateSpaceships()
{
    for(int i = 0; i < util::randomBetween(m_settings.spaceship_density, m_seed); i++)
    {
        Coords position = {util::random(0.0, (double)SCENE_WIDTH, m_seed), util::random(0.0, (double)SCENE_HEIGHT * 1 / 3, m_seed)};
        Rotation rotation;
        double scale = util::random(0.05, 0.1, m_seed);
        int type = util::random(4, 10, m_seed);

        rotation.x = position.getX();
        rotation.y = position.getY();
        double angle = 180;
        rotation.angle = util::random(-angle, angle, m_seed);

        m_satellites.push_back(FlyingObject(position, scale, rotation, type, m_seed));
    }
}

void Sky::generateSatellites()
{
    for(int i = 0; i < util::randomBetween(m_settings.satellite_density, m_seed); i++)
    {
        Coords position = {SCENE_WIDTH / 2, SURFACE_Y - SURFACE_R - (double)util::random(50, 200, m_seed)};
        Rotation rotation;
        double scale = util::random(0.1, 0.15, m_seed);
        int type = util::random(0, 3, m_seed);

        rotation.x = SURFACE_X;
        rotation.y = SURFACE_Y;
        double angle = 11;
        rotation.angle = util::random(-angle, angle, m_seed);

        m_satellites.push_back(FlyingObject(position, scale, rotation, type, m_seed));
    }
}

void Sky::draw(Svgfile& out)
{
     for(unsigned int i = 0; i < m_spaceships.size(); i++) // draw the planets
        m_spaceships[i].draw(out);

    for(unsigned int i = 0; i < m_satellites.size(); i++) // draw the planets
        m_satellites[i].draw(out);
}
