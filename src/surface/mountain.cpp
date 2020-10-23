#include "mountain.h"

Mountain::Mountain(Color color, double height) : Polygon()
{
    m_height = height;
    m_color = color;
    m_rotation.angle = 0;
}

Mountain::Mountain(std::vector<Coords> points, Color color, double height, double blur) : Polygon(points, color, blur)
{
    m_height = height;
}

Mountain::~Mountain()
{
    //dtor
}

void Mountain::draw(Svgfile& out, std::mt19937& seed)
{
    drawPolygon(out);

    if(m_height > 40)
        drawSnow(out, seed);

    drawShadow(out);
}

void Mountain::drawSnow(Svgfile& out, std::mt19937& seed)
{
    out.addPolygonClipPath(*this, this);

    out.addCircle(m_points[1].getX(), m_points[1].getY(), util::random(m_height * 0.2, m_height * 0.5, seed), 1, this, Color(255,255,255));
}

void Mountain::drawShadow(Svgfile& out)
{
    Polygon shadow;
    std::vector<Coords> points;
    Coords point;

    shadow.addPoint(m_points[0]);
    shadow.addPoint(m_points[1]);

    point.set(m_points[1].getX(), m_points[1].getY() + 100);
    shadow.addPoint(point);

    out.addPolygon(shadow.getPoints(), Color().withOpacity(0.3), m_rotation, nullptr, nullptr, 0);
}
