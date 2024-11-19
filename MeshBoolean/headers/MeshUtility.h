#pragma once
#include "RealPoint.h"
using namespace Geometry;


    class MeshUtility
    {
    public:
        MeshUtility();
        ~MeshUtility();

        RealPoint averagePoint(RealPoint& p1, RealPoint& p2, RealPoint& p3);
        double getAngleBetweenNormalAndXAxis(RealPoint& normal);
    };
