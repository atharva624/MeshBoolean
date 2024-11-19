#include "MeshUtility.h"
#include <cmath>
#define M_PI 3.14
using namespace Geometry;

MeshUtility::MeshUtility()
{
}

MeshUtility::~MeshUtility()
{
}

//The average point (centroid) of the triangle
RealPoint MeshUtility::averagePoint(RealPoint& p1, RealPoint& p2, RealPoint& p3) {
  
    // Extract x, y, z coordinates of the three input points
    double ax = p1.X();
    double ay = p1.Y();
    double az = p1.Z();

    double bx = p2.X();
    double by = p2.Y();
    double bz = p2.Z();

    double cx = p3.X();
    double cy = p3.Y();
    double cz = p3.Z();

    double avgX = (ax + bx + cx) / 3;
    double avgY = (ay + by + cy) / 3;
    double avgZ = (az + bz + cz) / 3;

    RealPoint avgPoint(avgX, avgY, avgZ);
    return avgPoint;
}

double MeshUtility::getAngleBetweenNormalAndXAxis(RealPoint& normal) {
    double nx = normal.X();
    double ny = normal.Y();
    double nz = normal.Z();

    double magnitude = std::sqrt(nx * nx + ny * ny + nz * nz);


    // Calculate the cosine of the angle using the dot product with the x-axis
    double cosTheta = nx / magnitude;

    // Compute the angle in radians, then convert it to degrees
    double angle = std::acos(cosTheta) * (180.0 / M_PI);
    return angle;
}


