#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(Color color, Rotation rotation, double blur = 0.0)
{
    m_color = color;
    m_blur = blur;
    m_rotation = rotation;
}

Polygon::Polygon(std::vector<Coords> points, Color color, double blur = 0.0)
{
    m_points = points;
    m_color = color;
    m_blur = blur;
}

Polygon::~Polygon()
{
    //dtor
}

void Polygon::flipVertically(FlipAnchor anchor)
{
    if(m_points.size() > 0)
    {
        if(anchor == FromRight)
        {
            double maxX = m_points[0].getX();

            for(unsigned int i = 1; i < m_points.size(); i++)
                if(m_points[i].getX() > maxX)
                maxX = m_points[i].getX();

            for(unsigned int i = 0; i < m_points.size(); i++)
            {
                double newX = 2 * maxX - m_points[i].getX();

                m_points[i].set(newX, m_points[i].getY());
            }
        }
    }
}

void Polygon::translate(Coords translation)
{
    for(unsigned int i = 0; i < m_points.size(); i++)
        m_points[i].set(m_points[i].getX() + translation.getX(), m_points[i].getY() + translation.getY());
}

void Polygon::addPoint(Coords position)
{
    m_points.push_back(position);
}

std::vector<Coords> Polygon::getPoints()
{
    return m_points;
}

void Polygon::drawPolygon(Svgfile& out)
{
    out.addPolygon(m_points, m_color, m_rotation, nullptr, this, m_blur);
}
