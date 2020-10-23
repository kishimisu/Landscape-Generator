#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>
#include <vector>
#include "../geometry/couleur.h"
#include "../geometry/coords.h"
#include "../geometry/gradient.h"
#include "util.h"
#include "../geometry/polygon.h"

#define SCENE_WIDTH 1000
#define SCENE_HEIGHT 600

#define SURFACE_X 500
#define SURFACE_Y 3000
#define SURFACE_R 2550

constexpr char defcol[] = "black";

class Polygon;

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=SCENE_WIDTH, int _height=SCENE_HEIGHT);
        ~Svgfile();

        void addDisk(double x, double y, double r, std::string color=defcol);

        void addCircle(double x, double y, double r, double ep, void* clipPathID, Color color);
        void addCircle(double x, double y, double r, double ep, Rotation rotation, void* clipPathID, Color color);
        void addCircleClipPath(double x, double y, double r, void* id);
        void addRadialGradient(Color color, void* id);
        void addRadialGradient(Gradient gradient);
        void addPolygon(std::vector<Coords> points, Color color, Rotation rotation, void* clipPathID, void* blurID, double blur);
        void addPolygonClipPath(Polygon polygon, void* id);
        void addPolygonClipPath(Polygon polygon, Rotation rotation, void* id);
        void addEllipse(double cx, double cy, double rx, double ry, Rotation rotation, Color color);
        void addEllipseWithGradient(double cx, double cy, double rx, double ry, Rotation rotation, Gradient gradient);
        void addShipBody(double x, double y, double width, double height, Rotation rotation, Color color);
        void addShipBodyClipPath(double x, double y, double width, double height, void* clipPathID);
        void addDebugLine(std::string debug);
        void addFlyingObject(double x, double y, double scale, Rotation rotation, int type);
        void addFlame(double x, double y, double scale, Rotation rotation, int type);
        void fileToSvg(std::string fileName, double x, double y, double scale, Rotation rotation, bool flame);
        void addEllipticalArc(double startX, double startY, double rx, double ry, Rotation rotation, int sweep_flag, double endX, double endY, double strokeWidth, Color top, Color bottom, std::string  id);
        void addLinearGradient(Color top, Color bottom, std::string id);

        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addLine(double x1, double y1, double x2, double y2, Rotation rotation, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        void addBackground(Color color);
        void addCircleWithGradient(Color color, double x, double y, double r, void* gradientID);
        void addCircleWithGradient(double x, double y, double r, Gradient gradient);

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED



