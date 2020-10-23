#include "flyingobject.h"

FlyingObject::FlyingObject(Coords position, double scale, Rotation rotation, int type, std::mt19937& seed)
{
    m_position = position;
    m_scale = scale;
    m_rotation = rotation;
    m_type = type;
    m_seed = seed;

    setupReactor();
}

FlyingObject::~FlyingObject()
{
    //dtor
}

void FlyingObject::setupReactor()
{
    double translateX_[3] = {-80, 0, 80};
    double translateX, translateY, correctScale;
    Coords position;
    Reactor reactor;

    switch(m_type)
    {
        case 4:
            for(int i = 0; i < 2; i++)
            {
                translateX = i == 0 ? 50 : 58;
                translateY = 220;
                position = Coords{m_position.getX() + translateX * m_scale * (i ? 1 : -1), m_position.getY() + translateY * m_scale};
                reactor = Reactor(position, m_scale, m_rotation, SmallFlame);

                m_reactors.push_back(reactor);
            }
        break;
        case 5:
            translateX = 0;
            translateY = 190;
            correctScale = m_scale * 0.9;
            position = Coords{m_position.getX() + translateX * correctScale, m_position.getY() + translateY * correctScale};
            reactor = Reactor(position, correctScale, m_rotation, BigFlame);

            m_reactors.push_back(reactor);
        break;
        case 6:
            translateX = 0;
            translateY = 320 - util::random(0,160,m_seed);
            correctScale = m_scale * 0.55;
            position = Coords{m_position.getX() + translateX * correctScale, m_position.getY() + translateY * correctScale};
            reactor = Reactor(position, correctScale, m_rotation, BigFlame);

            m_reactors.push_back(reactor);
        break;
        case 7:
            translateX = 170;
            translateY = 420 - util::random(0,130,m_seed);

            for(int i = 0; i < 2; i++)
            {
                correctScale = m_scale * 0.5;
                position = Coords{m_position.getX() + translateX * correctScale * (i ? 1 : -1), m_position.getY() + translateY * correctScale};
                reactor = Reactor(position, correctScale, m_rotation, SmallFlame);

                m_reactors.push_back(reactor);
            }
        break;
        case 8:
            translateY = 310 - util::random(0, 90,m_seed);

            for(int i = 0; i < 3; i++)
            {
                correctScale = m_scale * 0.65;
                position = Coords{m_position.getX() + translateX_[i] * correctScale, m_position.getY() + translateY * correctScale};
                reactor = Reactor(position, correctScale, m_rotation, i == 1 ? BigFlame : SmallFlame);

                m_reactors.push_back(reactor);
            }
        break;
        case 9:
            translateY = 345;

            for(int i = 0; i < 3; i++)
            {
                correctScale = m_scale * 0.6;
                position = Coords{m_position.getX() + translateX_[i] * correctScale, m_position.getY() + translateY * correctScale};
                reactor = Reactor(position, correctScale, m_rotation, i == 1 ? BigFlame : SmallFlame);

                m_reactors.push_back(reactor);
            }
        break;
        case 10:
            translateY = 300 - util::random(50,100,m_seed);

            for(int i = 0; i < 2; i++)
            {
                translateX =  i == 0 ? 190 : 200;
                correctScale = m_scale * 0.7;
                position = Coords{m_position.getX() + translateX * correctScale * (i ? 1 : -1), m_position.getY() + translateY * correctScale};
                reactor = Reactor(position, correctScale, m_rotation, SmallFlame);

                m_reactors.push_back(reactor);
            }
        break;
    }
}

void FlyingObject::draw(Svgfile& out)
{
    for(unsigned int i = 0; i < m_reactors.size(); i++)
        m_reactors[i].draw(out);

    out.addFlyingObject(m_position.getX(), m_position.getY(), m_scale, m_rotation, m_type);
}
