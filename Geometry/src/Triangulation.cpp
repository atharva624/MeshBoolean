#include "Triangulation.h"
#include "RealPoint.h"
#include <cmath>
#define M_PI 3.14

using namespace Geometry;

Triangulation::Triangulation()
{

}

Triangulation::~Triangulation()
{

}


RealPoint Geometry::Triangulation::getRealPoint(Point& p)
{
    double x;
    double y;
    double z;

    x = UniqueNumbers[p.X()];
    y = UniqueNumbers[p.Y()];
    z = UniqueNumbers[p.Z()];

    return RealPoint(x, y, z);
}