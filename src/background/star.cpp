#include "star.h"

Star::~Star()
{
    //dtor
}

/// draw the star
void Star::draw(Svgfile& out)
{
    out.addCircle(m_position.getX(), m_position.getY(), m_radius, 1, nullptr, m_color);
}
