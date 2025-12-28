#ifndef __Circle_h__
#define __Circle_h__

#include "curves/model3d/Curve.h"

#include "curves/math/Point.h"
#include "curves/math/Vector.h"

namespace curves {

namespace model3d {

using Point3d = math::Point<double, 3>;
using Vector3d = math::Vector<double, 3>;

class Circle : public Curve {
public:
    ~Circle() override;

    Point3d get_point(double t) const override;
    Vector3d get_first_derivative(double t) const override;

    double get_radius() { return _radius; };

private:
    explicit Circle(
        const Point3d& center, double radius, const Vector3d& plane_normal, const Vector3d& start_direction);

    Point3d _center; // Center of the circle
    double _radius; // Radius of the circle
    Vector3d _axis_x; // First axis in the plane of the circle
    Vector3d _axis_y; // Second axis in the plane, perpendicular to _axis_x

    friend class CurveFactory;
};

} // namespace model3d
} // namespace curves

#endif // __Circle_h__