#include "scene.h"

Scene::Scene(Settings settings)
{
    m_settings = settings;
    m_background = Background(m_settings);
    m_space = Space(m_settings);
    m_sky = Sky(m_settings);
    m_surface = Surface(m_settings);
}

Scene::~Scene()
{
    //dtor
}

/// draw the entire scene
void Scene::draw(Svgfile& out)
{
    m_background.draw(out);

    m_space.draw(out); // draw the space

    m_sky.draw(out);

    m_surface.draw(out, this); // draw the surface
}
