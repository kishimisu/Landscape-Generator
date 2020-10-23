#include "reactor.h"

Reactor::Reactor(Coords position, double scale, Rotation rotation, int type)
{
    m_position = position;
    m_scale = scale;
    m_type = type;
    m_rotation = rotation;
}

Reactor::~Reactor()
{
    //dtor
}

void Reactor::draw(Svgfile& out)
{
    out.addFlame(m_position.getX(), m_position.getY(), m_scale, m_rotation, m_type);
}
