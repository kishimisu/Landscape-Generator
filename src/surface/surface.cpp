#include "surface.h"

Surface::Surface(Settings settings)
{
    m_settings = settings;
    m_seed = settings.seeds[SurfaceSeed];
    m_position.set(SCENE_WIDTH / 2, SCENE_HEIGHT * 5);
    m_radius = SCENE_HEIGHT * 5 - SCENE_HEIGHT * 3 / 4;
    m_color = Color(true, m_seed);

    generateMountains();
    generateTrees();
}

Surface::~Surface()
{
    //dtor
}

void Surface::generateMountains()
{
    Coords position;

    double startAngle = M_PI - acos(SCENE_WIDTH / 2 / m_radius);
    double finalAngle = acos(SCENE_WIDTH / 2 / m_radius);

    double mountain_width;
    double mountain_height;

    double angle = startAngle+0.01;

    do
    {
        mountain_width = util::degToRad(util::random(0.8, 1.5, m_seed));
        mountain_height = mountain_width * 4000 * util::random(0.2, 0.7, m_seed);

        int random_composant = util::random(0, 60, m_seed);
        Color mountain_color = m_color - Color(random_composant);
        Mountain mountain(mountain_color, mountain_height);

        double endAngle = angle - mountain_width;
        double midAngle = (angle + endAngle) / 2;

        position.set(m_position.getX() + m_radius * cos(angle), m_position.getY() - m_radius * sin(angle));
        mountain.addPoint(position);

        position.set(m_position.getX() + (m_radius + mountain_height) * cos(midAngle), m_position.getY() - (m_radius + mountain_height) * sin(midAngle));
        mountain.addPoint(position);

        position.set(m_position.getX() + m_radius * cos(endAngle), m_position.getY() - m_radius * sin(endAngle));
        mountain.addPoint(position);

        m_moutains.push_back(mountain);

        angle -= util::random(mountain_width * 0.4, mountain_width * 0.7, m_seed);
    }while(angle > finalAngle);

    std::shuffle(m_moutains.begin(), m_moutains.end(), std::default_random_engine());
}

Color Surface::randomTreeColor(int colorSet, Color base_color)
{
    Color seasons[3][4] = { {Color(218, 120, 27), Color(212, 103, 25), Color(162,163,3), Color(144,170,6)},
                            {Color(114, 147, 43), Color(112, 227, 120), Color(109,146,38), Color(82,164,112)},
                            {Color(167, 59, 115), Color(227, 159, 176), Color(206,82,68), Color(231,174,178)} };

    Color first = Color(util::random(0,160, m_seed),util::random(160,255, m_seed),util::random(0,160, m_seed));
    Color white = Color(util::random(180, 255, m_seed));

    Color returnColor;

    if(colorSet < 3 )
        returnColor = seasons[colorSet][util::random(0, 3, m_seed)];
    else if(colorSet == 3)
        returnColor = first;
    else if(colorSet == 4)
        returnColor = white;
    else
        returnColor = base_color;

    if(colorSet != 3) returnColor.mutate2(30, m_seed);

    return returnColor;
}

void Surface::generateTrees()
{
    Coords position;

    double startAngle = M_PI - acos(SCENE_WIDTH / 2 / m_radius);
    double finalAngle = acos(SCENE_WIDTH / 2 / m_radius);
    double max_tree_size = 30.0;
    double min_tree_size = 4.0;
    double max_radius_ratio = 0.999;
    double min_radius_ratio = 0.950;
    int colorSet = util::random(0, 5, m_seed);

    for(int i = 0; i < util::randomBetween(m_settings.tree_density, m_seed); i++)
    {
        Rotation rotation = {util::radToDeg(util::random(finalAngle, startAngle, m_seed)), m_position.getX(), m_position.getY()};
        double new_radius_ratio = util::random(min_radius_ratio, max_radius_ratio, m_seed);
        const double root_radius = m_radius * new_radius_ratio;
        double new_radius = root_radius;
        double blur = (new_radius_ratio - min_radius_ratio) * 20;
        blur = 0;

        ///m = (y2 - y1) /  (x2 - x1);
        ///p = y1 - (m * x1);

        double m = (max_tree_size - min_tree_size) / (min_radius_ratio - max_radius_ratio);
        double p = min_tree_size - (m * max_radius_ratio);

        double tree_width =  (m * new_radius_ratio + p) * util::random(0.95, 1.05, m_seed);
        double tree_height = tree_width * util::random(2.0, 2.5, m_seed);

        std::vector<Polygon> segments;
        int segments_count = util::randomBetween(m_settings.tree_segments, m_seed);
        double segment_height = tree_height / (segments_count - 1);
        double segment_width = tree_width;

        Color tree_color = randomTreeColor(colorSet, m_color);

        Color final_color = tree_color - Color(20) * segments_count;
        Polygon trunk(Color(124,85,22), rotation, blur);

        double trunk_width = tree_width / util::random(5,10, m_seed);
        double trunk_height = tree_height / 8;

        position.set(m_position.getX() + new_radius - trunk_height, m_position.getY() - trunk_width);
        trunk.addPoint(position);

        position.set(m_position.getX() + new_radius + trunk_height, m_position.getY() - trunk_width);
        trunk.addPoint(position);

        position.set(m_position.getX() + new_radius + trunk_height, m_position.getY() + trunk_width);
        trunk.addPoint(position);

        position.set(m_position.getX() + new_radius - trunk_height, m_position.getY() + trunk_width);
        trunk.addPoint(position);

        segments.push_back(trunk);

        int tree_type = util::random(0, 12, m_seed);

        for(int j = 0; j < segments_count; j++)
        {
            Color segment_color;
            double top_radius = new_radius + segment_height;
            double mid_radius = new_radius + (top_radius - new_radius) * util::random(0.0, 0.25, m_seed);

            if(tree_type <= 3) segment_color = final_color + Color(20) * j;
            else if(tree_type <= 9) segment_color = tree_color - Color(20) * j;
            else segment_color = tree_color.mutate(20, m_seed);

            Polygon segment(segment_color, rotation, blur);

            position.set(m_position.getX() + new_radius, m_position.getY() - segment_width / 2);
            segment.addPoint(position);

            position.set(m_position.getX() + top_radius, m_position.getY());
            segment.addPoint(position);

            position.set(m_position.getX() + new_radius, m_position.getY() + segment_width / 2);
            segment.addPoint(position);

            position.set(m_position.getX() + mid_radius, m_position.getY());
            segment.addPoint(position);

            new_radius += segment_height / 2;
            if(j < segments_count - 1) segment_width *= util::random(0.65, 0.95, m_seed);

            segments.push_back(segment);
        }

        position.set(m_position.getX() + root_radius - trunk_height, m_position.getY());

        m_trees.push_back(Tree(segments, position, root_radius, tree_width, rotation, blur, Color(), m_seed));
    }

    std::sort(m_trees.begin(), m_trees.end());
}

/// draw the surface and its gradient
void Surface::draw(Svgfile& out, void* gradientID)
{
    out.addCircleWithGradient(Color(true, m_seed), m_position.getX(), m_position.getY(), m_radius, gradientID); // draw the gradient

    for(unsigned int i = 0; i < m_moutains.size(); i++)
        m_moutains[i].draw(out, m_seed);

    Color bottom_color = Color(true, m_seed);
    Gradient gradient{50, 50, 50, 50, 50, 98, 100, bottom_color, m_color - Color(40,40,40), this};
    out.addCircleWithGradient(m_position.getX(), m_position.getY(), m_radius, gradient);

    for(unsigned int i = 0; i < m_trees.size(); i++)
        m_trees[i].draw(out);
}
