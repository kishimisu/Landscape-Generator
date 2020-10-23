#include "tree.h"

Tree::Tree(std::vector<Polygon> segments, Coords position, double surfaceHeight, double width, Rotation rotation, double blur, Color color, std::mt19937& seed)
{
    m_segments = segments;
    m_surfaceHeight = surfaceHeight;
    m_width = width;
    m_rotation = rotation;
    m_position = position;
    m_color = color;
    m_blur = blur;
    m_seed = seed;
}

Tree::~Tree()
{
    //dtor
}

void Tree::print()
{
    std::cout << "TREE : ";
    m_segments[0].getPoints()[0].print();
    std::cout << std::endl << "\t" << "[angle: " << m_rotation.angle << ", x: " << m_rotation.x << ", y: " << m_rotation.y << "]" << std::endl;
}

void Tree::draw(Svgfile& out)
{
    drawTreeShadow(out);

    for(unsigned int i = 0; i < m_segments.size(); i++)
    {
        m_segments[i].drawPolygon(out);

        if(i == 0) drawTrunkShadow(m_segments[i], out);
        else       drawSegmentShadow(m_segments[i], out);
    }
}

void Tree::drawTreeShadow(Svgfile& out)
{
    Color gradientColor = Color(0);

    Gradient gradient{50, 50, 50, 50, 50, 0, 100, gradientColor.withOpacity(0.7), gradientColor.withOpacity(0), this};

    out.addEllipseWithGradient(m_position.getX(), m_position.getY(), m_width / 6, m_width / 2, m_rotation, gradient);
}

void Tree::drawSegmentShadow(Polygon& segment, Svgfile& out)
{
    Polygon shadow;

    double shadow_angle = util::degToRad(m_rotation.angle - 90 + util::random(-3,3, m_seed));

    shadow.addPoint(segment.getPoints()[0]);
    shadow.addPoint(segment.getPoints()[1]);
    shadow.addPoint(Coords(segment.getPoints()[1].getX() - 100 * cos(shadow_angle), segment.getPoints()[1].getY() - 100 * sin(shadow_angle)));

    out.addPolygonClipPath(segment, &segment);
    out.addPolygon(shadow.getPoints(), Color().withOpacity(0.3), m_rotation, &segment, &segment, m_blur);
}

void Tree::drawTrunkShadow(Polygon& trunk, Svgfile& out)
{
    Polygon shadow;

    double shadow_angle = util::degToRad(m_rotation.angle - 90 + util::random(-3,3, m_seed));
    double mid_y = (trunk.getPoints()[1].getY() + trunk.getPoints()[2].getY()) / 2;

    shadow.addPoint(trunk.getPoints()[0]);
    shadow.addPoint(trunk.getPoints()[1]);
    shadow.addPoint(Coords(trunk.getPoints()[1].getX(), mid_y));
    shadow.addPoint(Coords(trunk.getPoints()[1].getX() - 100 * cos(shadow_angle), mid_y - 100 * sin(shadow_angle)));

    out.addPolygonClipPath(trunk, &trunk);
    out.addPolygon(shadow.getPoints(), Color().withOpacity(0.3), m_rotation, &trunk, &trunk, m_blur);
}
