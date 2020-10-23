#include "planet.h"

Planet::Planet(Coords position, double radius, Color color, std::mt19937& seed)
{
    m_position = position;
    m_radius = radius;
    m_color = color;

    switch(util::random(0,1,seed)) // planet type
    {
        case 0: addCratersStyle_1(seed); break;
        case 1: addCratersStyle_2_3(util::random(0,1,seed), seed); break;
    }
}

void Planet::addCratersStyle_1(std::mt19937& seed)
{
    Coords position;
    double radius, x, y;
    double opacity;

    for(int i = 0; i < util::random(2,10,seed); i++)
    {
        do
        {
            radius = util::random(2.0, m_radius / 2, seed);
            x = util::random(m_position.getX() - m_radius, m_position.getX() + m_radius,seed);
            y = util::random(m_position.getY() - m_radius, m_position.getY() + m_radius,seed);
            opacity = util::random(0.1, 0.3,seed);
            position.set(x, y);

        }while(Crater(position, radius).isOverlaping(m_craters) || util::distanceBetween(position, m_position) > m_radius + radius);

        m_craters.push_back(Crater(position, radius, Color(0, 0, 0, opacity)));
    }
}

void Planet::addCratersStyle_2_3(bool shade, std::mt19937& seed)
{
    int ringCount = util::random(3, 6,seed);
    double angle = util::random(0.0, M_PI * 2,seed);

    int darker = util::random(0, 1,seed);

    for(int i = 0; i < ringCount; i++)
    {
        Coords position;

        double distance = util::random(m_radius, m_radius * 2 + m_radius / ringCount * i,seed);
        double x = m_position.getX() + distance * cos(angle) + util::random(-m_radius / 4, m_radius / 4,seed);
        double y = m_position.getY() + distance * sin(angle) + util::random(-m_radius / 4, m_radius / 4,seed);
        double opacity = util::random(0.03 * (7-ringCount), 0.2 - 0.01*(ringCount-2),seed);

        position.set(x, y);
        distance = util::distanceBetween(position, m_position);

        double radius = distance - m_radius + (ringCount-i-1) * m_radius * 2 / ringCount + util::random(-m_radius / ringCount / 2, m_radius / ringCount / 2,seed);

        if(shade)
        {
            if(darker)
                m_craters.push_back(Crater(position, radius, Color(0,0,0,opacity)));
            else
                m_craters.push_back(Crater(position, radius, Color(255,255,255,opacity)));
        }
        else
            m_craters.push_back(Crater(position, radius, m_color.mutate(60, seed)));
    }
}

Planet::~Planet()
{
    //dtor
}

/// console output of the planet informations
void Planet::print()
{
    std::cout << "PLANET " << this << " [position: ";
    m_position.print();
    std::cout << ", radius: " << m_radius << ", color: ";
    m_color.print();
    std::cout << ", craters: " << m_craters.size() << "]" << std::endl;

    for(unsigned int i = 0; i < m_craters.size(); i++)
    {
        std::cout << "\t";
        m_craters[i].print();
    }
}

/// draw the planet
void Planet::draw(Svgfile& out, std::mt19937& seed)
{
    Color gradientColor = m_color.mutate(100, seed);
    double gradientSize = util::random(m_radius * 1.1, m_radius * 1.6, seed);
    double gradientStart = util::random(0.0, 70.0,seed);
    Gradient gradient {50, 50, 50, 50, 50, gradientStart, 100, gradientColor, gradientColor.withOpacity(0), this};

    Color bottom = m_color;
    bottom.mutate2(50, seed);

    Color top = bottom;
    top.mutate2(50, seed);

    if(util::random(0, 10,seed) == 1)
        top = Color(true, seed);

    bool gotRing = (util::random(0, 5,seed) == 1);

    double ry = m_radius / util::random(2.0, 4.0,seed);
    double radius = m_radius * util::random(1.3, 1.7,seed);
    double strokeWidth = m_radius / util::random(1.5, 4.0,seed);
    Rotation rotation{util::random(-30.0, 30.0,seed), m_position.getX(), m_position.getY()};

    out.addCircleWithGradient(m_position.getX(), m_position.getY(), gradientSize, gradient);

    if(gotRing) drawRing(out, false, top, top, ry, radius, strokeWidth, rotation);

    out.addCircleClipPath(m_position.getX(), m_position.getY(), m_radius, this); // add clip path

    out.addCircle(m_position.getX(), m_position.getY(), m_radius, 1, nullptr, m_color); // draw the planet

    for(unsigned int i = 0; i < m_craters.size(); i++) // draw each crater, and clip them
        m_craters[i].draw(out, (void*)this);

    drawShadow(out, seed); // draw the planet's shadow

    if(gotRing) drawRing(out, true, top, bottom, ry, radius, strokeWidth, rotation);
}

/// draw the planet's shadow
void Planet::drawShadow(Svgfile& out, std::mt19937& seed)
{
    double distance = util::random(m_radius, m_radius * 2,seed);
    double x = m_position.getX() + distance * cos(M_PI * 3 / 4) + util::random(-m_radius / 4, m_radius / 4,seed);
    double y = m_position.getY() + distance * cos(M_PI * 3 / 4) + util::random(-m_radius / 4, m_radius / 4,seed);
    double radius = util::random(distance + m_radius * 0.4, distance + m_radius * 0.7,seed);
    double opacity = util::random(0.2, 0.4,seed);

    out.addCircle(x, y, radius, 1, this, Color(255, 255, 255, opacity));
}

std::string adresseRetour(void* id, std::string chaine)
{
    std::ostringstream oss;
    oss << id << chaine;
    return oss.str();
}

void Planet::drawRing(Svgfile& out, bool frontRing, Color top, Color bottom, double ry, double radius, double strokeWidth, Rotation rotation)
{
    if(frontRing)
        out.addEllipticalArc(m_position.getX() - radius, m_position.getY(), m_radius, ry, rotation, 0, m_position.getX() + radius, m_position.getY(), strokeWidth, top, bottom, adresseRetour(this, "front"));
    else
    {
        top = top - Color(50, 50, 50);
        out.addEllipticalArc(m_position.getX() - radius, m_position.getY(), m_radius, ry, rotation, 1, m_position.getX() + radius, m_position.getY(), strokeWidth, top, bottom, adresseRetour(this, "back"));
    }
}
