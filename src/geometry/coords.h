#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED

class Coords
{
    public :
        Coords(double x, double y);
        Coords();

        void print() const;
        void set();
        void set(double x, double y);

        double getX() const;
        double getY() const;

        friend Coords operator+(const Coords& c1, const Coords& c2);

    private :
        double m_x;
        double m_y;
};


#endif // COORDS_H_INCLUDED
