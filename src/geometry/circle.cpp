#include "circle.h"

Circle::Circle(Coords position, double radius, Color color)
{
    m_position = position;
    m_radius = radius;
    m_color = color;
    m_rotation.angle = 0;
}

Circle::Circle(Coords position, Rotation rotation, double radius, Color color)
{
    m_position = position;
    m_radius = radius;
    m_color = color;
    m_rotation = rotation;
}

Circle::~Circle()
{
    //dtor
}

void Circle::drawCircle(Svgfile& out)
{
    out.addCircle(m_position.getX(), m_position.getY(), m_radius, 1, m_rotation, nullptr, m_color);
}
