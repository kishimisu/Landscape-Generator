#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    std::cout << "Opening SVG output file : "
              << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, Rotation rotation, void* clipPathID, Color color)
{
    m_ostrm << "<circle "
        << attrib("cx", x)
        << attrib("cy", y)
        << attrib("r",  r)
        << attrib("fill", std::string(color))
        << attrib("stroke", std::string(color))
        << attrib("stroke-width", ep)
        << attrib("opacity", color.getOpacity());

    if(rotation.angle != 0)
        m_ostrm << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")");

    if(clipPathID != nullptr)
        m_ostrm << "clip-path=\"url(#" << clipPathID << ")\"";

    m_ostrm << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, void* clipPathID, Color color)
{
    m_ostrm << "<circle "
        << attrib("cx", x)
        << attrib("cy", y)
        << attrib("r",  r)
        << attrib("fill", std::string(color))
        << attrib("stroke", std::string(color))
        << attrib("stroke-width", ep)
        << attrib("opacity", color.getOpacity());

    if(clipPathID != nullptr)
        m_ostrm << "clip-path=\"url(#" << clipPathID << ")\"";

    m_ostrm << "/>\n";
}

void Svgfile::addCircleClipPath(double x, double y, double r, void* id)
{
    m_ostrm << "<clipPath "
            << attrib("id", id)
            << "> <circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r+0.5)
            << "/></clipPath>\n";
}

void Svgfile::addRadialGradient(Gradient gradient)
{
    m_ostrm << "<radialGradient "
            << "id=\"" << gradient.id << "grad" << "\" "
            << attrib("cx", util::doubleToString(gradient.cx) + "%")
            << attrib("cy", util::doubleToString(gradient.cy) + "%")
            << attrib("r", util::doubleToString(gradient.r) + "%")
            << attrib("fx", util::doubleToString(gradient.fx) + "%")
            << attrib("fy", util::doubleToString(gradient.fy) + "%")
            << ">\n<stop "
            << attrib("offset", util::doubleToString(gradient.offset[0]) + "%")
            << attrib("style", "stop-color:" + std::string(gradient.color[0]) + ";stop-opacity:" + util::doubleToString(gradient.color[0].getOpacity()))
            << " />\n<stop "
            << attrib("offset", util::doubleToString(gradient.offset[1]) + "%")
            << attrib("style", "stop-color:" + std::string(gradient.color[1]) + ";stop-opacity:" + util::doubleToString(gradient.color[1].getOpacity()))
            << " />\n</radialGradient>\n";
}

void Svgfile::addRadialGradient(Color color, void* id)
{
    m_ostrm << "<radialGradient "
            << attrib("id", id)
            << attrib("cx", "50%")
            << attrib("cy", "50%")
            << attrib("r", "50%")
            << attrib("fx", "50%")
            << attrib("fy", "50%")
            << ">\n<stop "
            << attrib("offset", "90%")
            << attrib("style", "stop-color:" + std::string(color) + ";stop-opacity:1.0")
            << " />\n<stop "
            << attrib("offset", "100%")
            << attrib("style", "stop-color:" + std::string(color) + ";stop-opacity:0.0")
            << " />\n</radialGradient>\n";
}

void Svgfile::addBackground(Color color)
{
    m_ostrm << "<rect "
        << attrib("width", "100%")
        << attrib("height", "100%")
        << attrib("fill", std::string(color))
        << attrib("opacity", color.getOpacity())
        << "/>\n";
}

void Svgfile::addCircleWithGradient(double x, double y, double r, Gradient gradient)
{
    addRadialGradient(gradient);

    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << "fill=" << "\"url(#" << gradient.id << "grad)\" "
            //<< "clip-path=\"url(#" << clipPathID << ")\""
            << "/>\n";
}

void Svgfile::addCircleWithGradient(Color color, double x, double y, double r, void* gradientID)
{
    addRadialGradient(color, gradientID);

    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r * 1.07)
            << "fill=" << "\"url(#" << gradientID << ")\" "
            //<< "clip-path=\"url(#" << clipPathID << ")\""
            << "/>\n";
}

void Svgfile::addPolygon(std::vector<Coords> points, Color color, Rotation rotation, void* clipPathID, void* blurID, double blur)
{
    if(blur > 0)
        m_ostrm << "<filter "
                << "id=\"" << blurID << "blur" << "\" "
                << attrib("x", 0)
                << attrib("y", 0)
                << "> <feGaussianBlur "
                << attrib("in", "SourceGraphic")
                << attrib("stdDeviation",  blur)
                << "/> </filter>\n";

    m_ostrm << "<polygon points=\"";

    for(unsigned int i = 0; i < points.size(); i++)
        m_ostrm << points[i].getX() << "," << points[i].getY() << " ";

    m_ostrm << "\" "
            << attrib("fill", std::string(color))
            << attrib("opacity", color.getOpacity());

    if(rotation.angle != 0)
        m_ostrm << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")");

    if(blur > 0)
        m_ostrm << "filter=" << "\"url(#" << blurID << "blur)\" ";

    if(clipPathID != nullptr)
        m_ostrm << "clip-path=\"url(#" << clipPathID << ")\"";

    m_ostrm << " />\n";
}

void Svgfile::addPolygonClipPath(Polygon polygon, void* id)
{
    m_ostrm << "<clipPath "
            << attrib("id", id)
            << "> <polygon points=\"";

    for(unsigned int i = 0; i < polygon.getPoints().size(); i++)
        m_ostrm << polygon.getPoints()[i].getX() << "," << polygon.getPoints()[i].getY() << " ";

    m_ostrm << "\" /></clipPath>\n";
}

void Svgfile::addPolygonClipPath(Polygon polygon, Rotation rotation, void* id)
{
    m_ostrm << "<clipPath "
            << attrib("id", id)
            << "> <polygon points=\"";

    for(unsigned int i = 0; i < polygon.getPoints().size(); i++)
        m_ostrm << polygon.getPoints()[i].getX() << "," << polygon.getPoints()[i].getY() << " ";

    m_ostrm << "\" ";

    if(rotation.angle != 0)
        m_ostrm << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")");

    m_ostrm << " /></clipPath>\n";
}

void Svgfile::addEllipse(double cx, double cy, double rx, double ry, Rotation rotation, Color color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", cx)
            << attrib("cy", cy)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("fill", std::string(color))
            << attrib("opacity", color.getOpacity())
            << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")")
            << " />\n";
}

void Svgfile::addEllipseWithGradient(double cx, double cy, double rx, double ry, Rotation rotation, Gradient gradient)
{
    addRadialGradient(gradient);

    m_ostrm << "<ellipse "
            << attrib("cx", cx)
            << attrib("cy", cy)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << "fill=" << "\"url(#" << gradient.id << "grad)\" "
            << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")")
            << " />\n";
}

void Svgfile::addShipBody(double x, double y, double width, double height, Rotation rotation, Color color)
{
    m_ostrm << "<path d=\"M "
            << x << "," << y
            << " h " << width / 2 << " v " << -height
            << " a " << width / 10 << " " << height / 5 << " 0 0 0 " << -width << ",0"
            << " v " << height << " h " << width / 2 << "\" "
            << attrib("fill", std::string(color));

    if(rotation.angle != 0)
        m_ostrm << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")");

    m_ostrm << " />\n";
}

void Svgfile::addShipBodyClipPath(double x, double y, double width, double height, void* clipPathID)
{
    m_ostrm << "<clipPath "
            << attrib("id", clipPathID)
            << "><path d=\"M "
            << x << "," << y
            << " h " << width / 2 << " v " << -height
            << " a " << width / 10 << " " << height / 5 << " 0 0 0 " << -width << ",0"
            << " v " << height << " h " << width / 2 << "\"";

    m_ostrm << " /></clipPath>\n";
}

void Svgfile::addDebugLine(std::string debug)
{
    m_ostrm << "<!--Debug: " << debug << "-->\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}

void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, Rotation rotation, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color);

    if(rotation.angle != 0)
        m_ostrm << attrib("transform", "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ")");

    m_ostrm << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}

std::string rotationToString(Rotation rotation)
{
    if(rotation.angle != 0)
       return "rotate(" + util::doubleToString(-rotation.angle) + "," + util::doubleToString(rotation.x) + "," + util::doubleToString(rotation.y) + ") ";

    return "";
}

std::string scaleToString(double scale)
{
    if(scale != 0)
        return "scale(" + util::doubleToString(scale) + ") ";

    return "";
}

std::string translateToString(double x, double y)
{
    if(x != 0 || y != 0)
        return "translate(" + util::doubleToString(x) + " " + util::doubleToString(y) + ") ";

    return "";
}

void Svgfile::fileToSvg(std::string fileName, double x, double y, double scale, Rotation rotation, bool flame)
{
    std::string line, hexColor;
    std::ifstream file(fileName, std::ios::in);
    size_t endLine, color;
    Color rgbColor;

    if(file)
    {
        while(getline(file, line))
        {
            color = line.find("#");

            hexColor = line.substr(color+1, 6);

            rgbColor = util::hexToColor(hexColor);
            //rgbColor.mutate2(10, std::);
            line.replace(color, 7, std::string(rgbColor));

            endLine = line.find("/>");
            line = line.substr(0, endLine);

            m_ostrm << line
                   << " transform=\""
                   << rotationToString(rotation)
                   << translateToString(x, y)
                   << scaleToString(scale);

            if(flame)
                m_ostrm << "rotate(-135) ";

            m_ostrm << "\" />\n";
        }

        file.close();
    }
    else std::cerr << "Impossible d'ouvrir le  fichier " << fileName << std::endl;
}

void Svgfile::addFlyingObject(double x, double y, double scale, Rotation rotation, int type)
{
    std::string fileName = "src/imgs/flyingObject_";
    fileName += std::to_string(type);
    fileName += ".svg";

    fileToSvg(fileName.c_str(), x, y, scale, rotation, false);
}

void Svgfile::addFlame(double x, double y, double scale, Rotation rotation, int type)
{
    std::string fileName = "src/imgs/flame_";
    fileName += std::to_string(type);
    fileName += ".svg";

    fileToSvg(fileName.c_str(), x, y, scale, rotation, true);
    //addCircle(x, y, 20 * scale, 1, rotation, nullptr, Color(255,0,0));
}

void Svgfile::addEllipticalArc(double startX, double startY, double rx, double ry, Rotation rotation, int sweep_flag, double endX, double endY, double strokeWidth, Color top, Color bottom, std::string id)
{
    addLinearGradient(top, bottom, id);

    m_ostrm << "<path d=\"M " << startX << " " << startY
            << "A " << rx << " " << ry << " 0 0 " << sweep_flag << " " << endX << " " <<  endY << "\" "
            << attrib("stroke-width", strokeWidth)
            << attrib("fill", "none")
            << "stroke=\"url(#" << id << "linear)\" "
            << attrib("transform", rotationToString(rotation))
            << "/>\n";
}

void Svgfile::addLinearGradient(Color top, Color bottom, std::string id)
{
    m_ostrm << "<linearGradient "
            << "id=\"" << id << "linear\" "
            << attrib("x1", "0%")
            << attrib("y1", "0%")
            << attrib("x2", "0%")
            << attrib("y2", "100%")
            << " >\n";

    for(int i = 0; i < 2; i++)
    {
        m_ostrm << "<stop "
            << attrib("offset", i == 0 ? "0%" : "100")
            << attrib("style", "stop-color:" + std::string(i == 0 ? top : bottom) + ";")
            << "/>\n";
    }

    m_ostrm << "</linearGradient>\n";
}
