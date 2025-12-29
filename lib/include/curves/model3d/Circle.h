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

    bool belongs(const Point3d& point, double precision) const;

    const Point3d& get_center() const { return _center; };
    double get_radius() const { return _radius; };
    const Vector3d& get_axis() const { return _axis; };
    const Vector3d& get_axis_x() const { return _axis_x; };
    const Vector3d& get_axis_y() const { return _axis_y; };

private:
    explicit Circle(
        const Point3d& center, double radius, const Vector3d& plane_normal, const Vector3d& start_direction);

    Point3d _center;
    double _radius;
    Vector3d _axis; // Circle axis direction (normalized). Redundant, stored only to speed up computations
    Vector3d _axis_x; // First axis in the plane of the circle (normalized)
    Vector3d _axis_y; // Second axis in the plane, perpendicular to _axis_x (normalized)

    friend class CurveFactory;
};

} // namespace model3d
} // namespace curves

#endif // __Circle_h__