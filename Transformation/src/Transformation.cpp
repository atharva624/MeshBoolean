#include "Transformation.h"
#include "Matrix4x4.h"
#include <map>
#include <cmath>
#define TOLERANCE 0.0000001
#define PI 3.14159265359

using namespace Geometry;

bool Transformation::Transformation::operator()(double a, double b) const
{
    return fabs(a - b) > TOLERANCE ? a < b : false;
}

Triangulation Transformation::Transformation::scaling(Triangulation& triangulation, double scale_x, double scale_y, double scale_z)
{
    Geometry::Matrix4x4 matrix;
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    matrix.matrix[0][0] = scale_x;
    matrix.matrix[1][1] = scale_y;
    matrix.matrix[2][2] = scale_z;
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            nmatrix = matrix.multiply(triangulation.UniqueNumbers[pt.X()], triangulation.UniqueNumbers[pt.Y()], triangulation.UniqueNumbers[pt.Z()]);
            int pts[3];
            for (int i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}

Triangulation Transformation::Transformation::translation(Triangulation& triangulation, double translate_x, double translate_y, double translate_z)
{
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    Geometry::Matrix4x4 matrix;
    matrix.matrix[0][3] = translate_x;
    matrix.matrix[1][3] = translate_y;
    matrix.matrix[2][3] = translate_z;
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            nmatrix = matrix.multiply(triangulation.UniqueNumbers[pt.X()], triangulation.UniqueNumbers[pt.Y()], triangulation.UniqueNumbers[pt.Z()]);
            int pts[3];
            for (int i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}

Triangulation Transformation::Transformation::rotation_x(Triangulation& triangulation, double rotate_x)
{
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    Geometry::Matrix4x4 matrix;
    matrix.matrix[1][1] = cos((rotate_x * PI) / 180);
    matrix.matrix[1][2] = -sin((rotate_x * PI) / 180);
    matrix.matrix[2][1] = sin((rotate_x * PI) / 180);
    matrix.matrix[2][2] = cos((rotate_x * PI) / 180);
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            nmatrix = matrix.multiply(triangulation.UniqueNumbers[pt.X()], triangulation.UniqueNumbers[pt.Y()], triangulation.UniqueNumbers[pt.Z()]);
            int pts[3];
            for (int i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}

Triangulation Transformation::Transformation::rotation_y(Triangulation& triangulation, double rotate_y)
{
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    Geometry::Matrix4x4 matrix;
    matrix.matrix[0][0] = cos((rotate_y * PI) / 180);
    matrix.matrix[2][0] = -sin((rotate_y * PI) / 180);
    matrix.matrix[0][2] = sin((rotate_y * PI) / 180);
    matrix.matrix[2][2] = cos((rotate_y * PI) / 180);
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            nmatrix = matrix.multiply(triangulation.UniqueNumbers[pt.X()], triangulation.UniqueNumbers[pt.Y()], triangulation.UniqueNumbers[pt.Z()]);
            int pts[3];
            for (int i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}

Triangulation Transformation::Transformation::rotation_z(Triangulation& triangulation, double rotate_z)
{
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    Geometry::Matrix4x4 matrix;
    matrix.matrix[0][0] = cos((rotate_z * PI) / 180);
    matrix.matrix[0][1] = -sin((rotate_z * PI) / 180);
    matrix.matrix[1][0] = sin((rotate_z * PI) / 180);
    matrix.matrix[1][1] = cos((rotate_z * PI) / 180);
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            nmatrix = matrix.multiply(triangulation.UniqueNumbers[pt.X()], triangulation.UniqueNumbers[pt.Y()], triangulation.UniqueNumbers[pt.Z()]);
            int pts[3];
            for (int i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}