#include "crater.h"

Crater::Crater(Coords position, int radius, Color color)
{
    m_position = position;
    m_radius = radius;
    m_color = color;
}

Crater::Crater(Coords position, int radius)
{
    m_position = position;
    m_radius = radius;
}

Crater::~Crater()
{
    //dtor
}

/// console output of the crater informations
void Crater::print()
{
    std::cout << "CRATER " << this << " [position: ";
    m_position.print();
    std::cout << ", radius: " << m_radius << ", color: ";
    m_color.print();
    std::cout << "] " << std::endl;
}

/// return true if the crater is overlaping at least one of the other craters
bool Crater::isOverlaping(std::vector<Crater> craters)
{
    for(unsigned int i = 0; i < craters.size(); i++)
        if(m_position.getX() + m_radius > craters[i].m_position.getX() - craters[i].m_radius &&
           m_position.getX() - m_radius < craters[i].m_position.getX() + craters[i].m_radius &&
           m_position.getY() + m_radius > craters[i].m_position.getY() - craters[i].m_radius &&
           m_position.getY() - m_radius < craters[i].m_position.getY() + craters[i].m_radius)
            return true;

    return false;
}

/// draw the crater
void Crater::draw(Svgfile& out, void* clipPathID)
{
    out.addCircle(m_position.getX(), m_position.getY(), m_radius, 1, clipPathID, m_color);
}
