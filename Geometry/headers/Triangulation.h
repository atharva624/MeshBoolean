#pragma once
#include "Triangle.h"
#include "RealPoint.h"
#include<vector>

namespace Geometry
{
    class Triangulation
    {
    public:
        Triangulation();
        ~Triangulation();

        std::vector<double> UniqueNumbers;
        std::vector<Triangle> Triangles;
        RealPoint getRealPoint(Point& p);

       

    private:
        std::vector<Point> points;
        std::vector<Triangle> triangles; 
    };
}