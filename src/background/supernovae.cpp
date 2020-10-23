#include "supernovae.h"

Supernovae::~Supernovae()
{
    //dtor
}

void Supernovae::draw(Svgfile& out, std::mt19937& seed)
{
    double gradientStart = util::random(0, 30, seed);
    Gradient gradient{50, 50, 50, 50, 50, gradientStart, 100, m_color, m_color.withOpacity(0), this};

    out.addCircleWithGradient(m_position.getX(), m_position.getY(), m_radius, gradient);
}
