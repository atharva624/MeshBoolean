#include "TransformationManager.h"
#include "Triangulation.h"
using namespace Geometry;

TransformationManager::TransformationManager()
{

}

TransformationManager::~TransformationManager()
{

}

std::vector<Triangulation> TransformationManager::transformObject(std::vector<Triangulation>& triangulation)
{
    Triangulation TranslationTriangulation;
    Triangulation RotationTriangulation;
    Triangulation ReverseRotationTriangulation;
    Triangulation ReverseTranslationTriangulation;

    Triangulation TranslationTriangulation2;
    Triangulation RotationTriangulation2;
    Triangulation ReverseRotationTriangulation2;
    Triangulation ReverseTranslationTriangulation2;

    Geometry::Triangle triangle1 = triangulation[0].Triangles[0];
    Geometry::Triangle triangle2 = triangulation[1].Triangles[0];

    Geometry::Point firstNormalPoint = triangle1.Normal();
    Geometry::RealPoint firstNormal = triangulation[0].getRealPoint(firstNormalPoint);

    Geometry::Point secondNormalPoint = triangle2.Normal();
    Geometry::RealPoint secondNormal = triangulation[1].getRealPoint(secondNormalPoint);


    double angle1 = mesh.getAngleBetweenNormalAndXAxis(firstNormal);
    double angle2 = mesh.getAngleBetweenNormalAndXAxis(secondNormal);


    // First Triangle avg
    Point firstTriangleP1 = triangle1.P1();
    Point firstTriangleP2 = triangle1.P2();
    Point firstTriangleP3 = triangle1.P3();
    //RealPoint of First Triangle avg
    RealPoint firstRealPoint1 = triangulation[0].getRealPoint(firstTriangleP1);
    RealPoint firstRealPoint2 = triangulation[0].getRealPoint(firstTriangleP2);
    RealPoint firstRealPoint3 = triangulation[0].getRealPoint(firstTriangleP3);
    Geometry::RealPoint avgFirstTriangle = mesh.averagePoint(firstRealPoint1, firstRealPoint2, firstRealPoint3);
  
    TranslationTriangulation = t.translation(triangulation[0], -(avgFirstTriangle.X()), -(avgFirstTriangle.Y()), -(avgFirstTriangle.Z()));
    RotationTriangulation = t.rotation_x(TranslationTriangulation, -angle1);

    // Second Triangle average
    Point secondTriangleP1 = triangle2.P1();
    Point secondTriangleP2 = triangle2.P2();
    Point secondTriangleP3 = triangle2.P3();
    //RealPoint of Second Triangle average
    RealPoint secondRealPoint1 = triangulation[1].getRealPoint(secondTriangleP1);
    RealPoint secondRealPoint2 = triangulation[1].getRealPoint(secondTriangleP2);
    RealPoint secondRealPoint3 = triangulation[1].getRealPoint(secondTriangleP3);
    Geometry::RealPoint avgSecondTriangle = mesh.averagePoint(secondRealPoint1, secondRealPoint2, secondRealPoint3);


    TranslationTriangulation2 = t.translation(triangulation[1], -(avgSecondTriangle.X()), -(avgSecondTriangle.Y()), -(avgSecondTriangle.Z()));
    RotationTriangulation2 = t.rotation_x(TranslationTriangulation2, -angle2);
    
    ReverseRotationTriangulation = t.rotation_x(TranslationTriangulation, angle1);
    ReverseRotationTriangulation2 = t.rotation_x(TranslationTriangulation2, angle1);

    ReverseTranslationTriangulation = t.translation(ReverseRotationTriangulation, (avgFirstTriangle.X()), (avgFirstTriangle.Y()), (avgFirstTriangle.Z()));
    ReverseTranslationTriangulation2 = t.translation(ReverseRotationTriangulation2, (avgFirstTriangle.X()), (avgFirstTriangle.Y()), (avgFirstTriangle.Z()));
    std::vector<Triangulation> resultTriangulation;
    resultTriangulation.push_back(ReverseTranslationTriangulation);
    resultTriangulation.push_back(ReverseTranslationTriangulation2);

    return resultTriangulation;
}
