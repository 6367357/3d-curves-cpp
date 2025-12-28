#ifndef __Ellipse_h__
#define __Ellipse_h__

#include "curves/model3d/Curve.h"

#include "curves/math/Point.h"
#include "curves/math/Vector.h"

namespace curves {

namespace model3d {

using Point3d = math::Point<double, 3>;
using Vector3d = math::Vector<double, 3>;

class Ellipse : public Curve {
public:
    ~Ellipse() override;

    Point3d get_point(double t) const override;
    Vector3d get_first_derivative(double t) const override;

private:
    explicit Ellipse(const Point3d& center,
        double radius_major,
        double radius_minor,
        const Vector3d& plane_normal,
        const Vector3d& major_direction);

    Point3d _center; // Center of the ellipse
    double _radius_major; // Semi-major axis (largest radius)
    double _radius_minor; // Semi-minor axis (smallest radius)
    Vector3d _axis_x; // Direction vector of the semi-major axis in the plane
    Vector3d _axis_y; // Direction vector of the semi-minor axis in the plane

    friend class CurveFactory;
};

} // namespace model3d
} // namespace curves

#endif // __Ellipse_h__