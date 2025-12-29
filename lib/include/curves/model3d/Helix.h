#ifndef __Helix_h__
#define __Helix_h__

#include "curves/model3d/Curve.h"

#include "curves/math/Point.h"
#include "curves/math/Vector.h"

namespace curves {

namespace model3d {

using Point3d = math::Point<double, 3>;
using Vector3d = math::Vector<double, 3>;

class Helix : public Curve {
public:
    ~Helix() override;

    Point3d get_point(double t) const override;
    Vector3d get_first_derivative(double t) const override;

    const Point3d& get_center() const { return _center; };
    double get_radius() const { return _radius; };
    double get_step() const { return _step; };
    const Vector3d& get_axis() const { return _axis; };
    const Vector3d& get_axis_x() const { return _axis_x; };
    const Vector3d& get_axis_y() const { return _axis_y; };

private:
    explicit Helix(
        const Point3d& center, double radius, double step, const Vector3d& axis, const Vector3d& start_direction);

    Point3d _center; // Center point of the helix
    double _radius; // Radius of the helix
    double _step; // Step per full revolution
    Vector3d _axis; // Helix axis direction (normalized). Redundant, stored only to speed up computations
    Vector3d _axis_x; // First orthogonal axis perpendicular to _axis (normalized)
    Vector3d _axis_y; // Second orthogonal axis perpendicular to _axis (normalized)

    friend class CurveFactory;
};

} // namespace model3d
} // namespace curves

#endif // __Helix_h__