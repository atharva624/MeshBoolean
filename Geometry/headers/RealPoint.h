#pragma once

namespace Geometry {

    class RealPoint {
        double mX;
        double mY;
        double mZ;

    public:
        RealPoint();
        RealPoint(double x, double y, double z);
        ~RealPoint();

        double X() const;
        double Y() const;
        double Z() const;

        bool operator<(const RealPoint& other) const;
        bool operator==(const RealPoint& other) const;
    };

} 
