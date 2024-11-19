#include "RealPoint.h"

namespace Geometry {
    RealPoint::RealPoint()
        : mX(0.0), mY(0.0), mZ(0.0) {}

    RealPoint::RealPoint(double x, double y, double z)
        : mX(x), mY(y), mZ(z) {}

    RealPoint::~RealPoint() {

    }

    double RealPoint::X() const {
        return mX;
    }

    double RealPoint::Y() const {
        return mY;
    }

    double RealPoint::Z() const {
        return mZ;
    }

    bool RealPoint::operator<(const RealPoint& other) const {
        if (mX != other.mX) {
            return mX < other.mX;
        }
        if (mY != other.mY) {
            return mY < other.mY;
        }
        return mZ < other.mZ;
    }

    bool RealPoint::operator==(const RealPoint& other) const {
        return (mX == other.mX && mY == other.mY && mZ == other.mZ);
    }

} 
