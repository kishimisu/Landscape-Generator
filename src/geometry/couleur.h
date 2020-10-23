#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

#include <string>
#include <cstdint>
#include <random>

class Color
{
    public :
        Color(int color);
        Color(bool randomtoire, std::mt19937& seed, double opacity = 1.0);
        Color(uint8_t rouge, uint8_t vert, uint8_t bleu, double opacity = 1.0);
        Color();
        void print() const;
        void set();

        double getOpacity();

        Color mutate(int ecart, std::mt19937& seed);
        void mutate2(double amplitude, std::mt19937& seed);
        Color withOpacity(double opacity);

        operator std::string() const;
        Color operator+(Color color);
        Color operator-(Color color);
        Color operator*(int j);

    private :
        // uint8_t �quivalent � unsigned char :
        // unsigned 8 bits (8 bits non sign�)
        uint8_t m_rouge, m_vert, m_bleu;
        double m_opacity;
};

#endif // COULEUR_H_INCLUDED
