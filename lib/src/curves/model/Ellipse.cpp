#include "curves/model3d/Ellipse.h"

#include "curves/math/LinearAlgebra.h"
#include "curves/model3d/Curve.h"

namespace curves {
namespace model3d {

Ellipse::Ellipse(const Point3d& center,
    double radius_major,
    double radius_minor,
    const Vector3d& plane_normal,
    const Vector3d& major_direction)
    : _center{center}, _radius_major{radius_major}, _radius_minor{radius_minor}, _axis_x{major_direction},
      _axis_y{math::cross_product(plane_normal, major_direction)} {};

Ellipse::~Ellipse() = default;

Point3d Ellipse::get_point(double t) const {
    // Formula: P(t) = C + a * cos(t) * U + b * sin(t) * V
    // Where U is _axis_x and V is _axis_y
    // Where a is _radius_major and b is _radius_minor
    // Counterclockwise rotation

    const auto cos{std::cos(t)};
    const auto sin{std::sin(t)};

    const auto offset_u{_axis_x * (cos * _radius_major)}; // a * cos(t) * U
    const auto offset_v{_axis_y * (sin * _radius_minor)}; // b * sin(t) * V

    const auto offset{offset_u + offset_v};

    return math::translate(_center, offset);
}

Vector3d Ellipse::get_first_derivative(double t) const {
    // Formula: P'(t) = b * cos(t) * V - a * sin(t) * U
    // Where U is _axis_x and V is _axis_y
    // Where a is _radius_major and b is _radius_minor

    const auto cos{std::cos(t)};
    const auto sin{std::sin(t)};

    const auto offset_v{_axis_y * (cos * _radius_minor)}; // b * cos(t) * V
    const auto offset_u{_axis_x * (sin * _radius_major)}; // a * sin(x) * U

    return offset_v - offset_u;
}

} // namespace model3d
} // namespace curves