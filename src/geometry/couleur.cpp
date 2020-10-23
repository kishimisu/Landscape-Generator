#include "couleur.h"
#include "../others/svgfile.h"
#include "../others/util.h"
#include <iostream>

Color::Color(bool randomtoire, std::mt19937& seed, double opacity)
{
    if(randomtoire)
    {
        m_rouge = util::random(0,255,seed);
        m_vert = util::random(0,255,seed);
        m_bleu = util::random(0,255,seed);
    }
    else
    {
        m_rouge = 0;
        m_vert = 0;
        m_bleu = 0;
    }

    m_opacity = opacity;
}

Color::Color(int color)
{
    m_rouge = color;
    m_bleu = color;
    m_vert = color;

    m_opacity = 1.0;
}

Color::Color(uint8_t rouge, uint8_t vert, uint8_t bleu, double opacity)
    : m_rouge{rouge}, m_vert{vert}, m_bleu{bleu}, m_opacity{opacity}
{ }


Color::Color()
    : Color(0, 0, 0) // Délégation de constructeur
{ }


void Color::print() const
{
    std::cout << "(" << (int)m_rouge << ", " << (int) m_vert << ", " << (int)m_bleu << ", " << m_opacity << ")";
}

uint8_t saisirCanal()
{
    int val;
    std::cin >> val;
    while (val<0 || val>255)
    {
        std::cout << "Mauvaise valeur color, recommencer : ";
        util::videCin();
        std::cin >> val;
    }

    return (uint8_t)val;
}

void Color::set()
{
    std::cout << "Veuillez saisir rouge vert et bleu SVP : ";
    m_rouge = saisirCanal();
    m_vert = saisirCanal();
    m_bleu = saisirCanal();
}

Color Color::mutate(int ecart, std::mt19937& seed)
{
    int maxOffset = util::min(255 - m_rouge, 255 - m_bleu, 255 - m_vert);
    int minOffset = util::min(m_rouge, m_bleu, m_vert);

    int offset = util::random(std::max(-ecart,-minOffset), std::min(ecart, maxOffset), seed);

    if(offset > 0)
        return Color(m_rouge, m_vert, m_bleu, m_opacity) + Color(offset, offset, offset);
    else
        return Color(m_rouge, m_vert, m_bleu, m_opacity) - Color(-offset, -offset, -offset);
}

Color Color::withOpacity(double opacity)
{
    return Color(m_rouge, m_vert, m_bleu, opacity);
}

Color Color::operator+(Color color)
{
    return Color(std::min(m_rouge + color.m_rouge, 255), std::min(m_vert + color.m_vert, 255), std::min(m_bleu + color.m_bleu, 255), m_opacity);
}
Color Color::operator-(Color color)
{
    return Color(std::max(m_rouge - color.m_rouge, 0), std::max(m_vert - color.m_vert, 0), std::max(m_bleu - color.m_bleu, 0), m_opacity);
}

Color::operator std::string() const
{
    return Svgfile::makeRGB(m_rouge, m_vert, m_bleu);
}

Color Color::operator*(int j)
{
    return Color(m_rouge * j, m_vert * j, m_bleu * j, m_opacity);
}

double Color::getOpacity()
{
    return m_opacity;
}

uint8_t mutateCanal(uint8_t v, double amplitude, std::mt19937& seed)
{
    int val=v;

    val += util::random(-amplitude, amplitude, seed);

    if ( val<0 )
        val = 0;

    if ( val>255 )
        val = 255;

    return (uint8_t)val;
}


void Color::mutate2(double amplitude, std::mt19937& seed)
{
    m_rouge = mutateCanal(m_rouge, amplitude, seed);
    m_vert = mutateCanal(m_vert, amplitude, seed);
    m_bleu = mutateCanal(m_bleu, amplitude, seed);
}
