#include "blackhole.h"

BlackHole::BlackHole(Coords position, Color color, double radius)
{
    m_position = position;
    m_radius = radius;
    m_rotation.angle = 0;
    m_color = color;
}

BlackHole::~BlackHole()
{
    //dtor
}

void BlackHole::draw(Svgfile& out, std::mt19937& seed)
{
    Color gradientColor = Color(255);
    double gradientStart = util::random(0.0, 70.0, seed);

    gradientStart = 40;
    Gradient gradient{50, 50, 50, 50, 50, gradientStart, 100, gradientColor, gradientColor.withOpacity(0), this};

    out.addCircleWithGradient(m_position.getX(), m_position.getY(), m_radius * 1.3, gradient);
    Circle::drawCircle(out);

    double stars_count = m_radius * util::random(1, 20, seed);

    for(int i = 0; i < stars_count; i++)
    {
        double angle = util::random(0.0, 2.0 * M_PI, seed);
        double radius = m_radius * util::random(1.0, 1.3, seed);
        double x = m_position.getX() + radius * cos(angle);
        double y = m_position.getY() - radius * sin(angle);
        double star_radius = util::random(0.01,0.5, seed);

        out.addCircle(x, y, star_radius, 0, nullptr, Color(255));
    }
}
