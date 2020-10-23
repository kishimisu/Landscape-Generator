#include "background.h"

Background::Background(Settings settings)
{
    m_settings = settings;
    m_seed = m_settings.seeds[BackgroundSeed];

    m_color = Color(0,0, util::random(0,70, m_seed));

    generateStars();

    for(int i = 0; i < util::randomBetween(m_settings.supernovae_density, m_seed); i++)
        addSupernovae();

    generateBlackHoles();
}

Background::~Background()
{
    //dtor
}

void Background::generateStars()
{
    for(int i = 0; i < util::randomBetween(m_settings.star_density, m_seed); i++)
    {
        double x = util::random(0, SCENE_WIDTH, m_seed);
        double y = util::random(0, SCENE_HEIGHT, m_seed);
        double radius = util::randomBetween(m_settings.star_size, m_seed);

        addStar(x, y, radius);
    }

    for(int i = 0; i < util::random(0,5, m_seed); i++)
    {
        double origin_x = util::random(0, SCENE_WIDTH, m_seed);
        double origin_y = util::random(0, SCENE_HEIGHT, m_seed);
        double max_r = util::random(30, 100, m_seed);

        for(int j = 0; j < util::random(50, 200, m_seed); j++)
        {
            double angle = util::random(0.0, 2.0 * M_PI, m_seed);
            double radius = util::random(0.0, max_r, m_seed);
            double x = origin_x + radius * cos(angle);
            double y = origin_y - radius * sin(angle);
            double star_radius = util::random(m_settings.star_size[0],m_settings.star_size[1] / 2, m_seed);

            addStar(x, y, star_radius);
        }
    }
}

void Background::generateBlackHoles()
{
    for(int i = 0; i < util::randomBetween(m_settings.blackhole_density, m_seed); i++)
    {
        double x = util::random(0, SCENE_WIDTH, m_seed);
        double y = util::random(0, SCENE_HEIGHT, m_seed);
        double r = util::random(10, 40, m_seed);

        m_blackHoles.push_back(BlackHole({x, y}, m_color - Color(30, 30, 30), r));
    }
}

/// add a star to the space
void Background::addStar(double x, double y, double radius)
{
    Coords position;

    int r = 255;
    int v = 255;
    int b = 255;

    int star_type = util::random(0,50, m_seed);
    int offset = util::random(20,255, m_seed);

    if(star_type == 0) // blue star
        b -= offset;
    else if (star_type == 1) // red star
    {
        v -= offset;
        b -= offset;
    }

    Color color(r, v, b);

    position.set(x, y);

    m_stars.push_back(Star(position, radius, color));
}

void Background::addSupernovae()
{
    Coords position;

    double x = util::random(0, SCENE_WIDTH, m_seed);
    double y = util::random(0, SCENE_HEIGHT, m_seed);
    double radius = util::random(m_settings.star_size[0] * 10, m_settings.star_size[1] * 14, m_seed);

    int r = 255;
    int v = 255;
    int b = 255;

    int star_type = util::random(0,5, m_seed);
    int offset = util::random(20,255, m_seed);

    if(star_type == 0) // blue star
        b -= offset;
    else if (star_type == 1) // red star
    {
        v -= offset;
        b -= offset;
    }

    Color color(r, v, b);

    position.set(x, y);

    m_supernovaes.push_back(Supernovae(position, radius, color));
}

/// draw the space
void Background::draw(Svgfile& out)
{
    out.addBackground(m_color);

    for(unsigned int i = 0; i < m_stars.size(); i++)
        m_stars[i].draw(out);

    for(unsigned int i = 0; i < m_supernovaes.size(); i++)
        m_supernovaes[i].draw(out, m_seed);

    for(unsigned int i = 0; i < m_blackHoles.size(); i++)
        m_blackHoles[i].draw(out, m_seed);

}
