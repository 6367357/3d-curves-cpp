#include "curves/model3d/Circle.h"

#include "curves/math/LinearAlgebra.h"

namespace curves {
namespace model3d {

Circle::Circle(const Point3d& center, double radius, const Vector3d& plane_normal, const Vector3d& start_direction)
    : _center{center}, _radius{radius}, _axis_x{start_direction},
      _axis_y{math::cross_product(plane_normal, start_direction)} // normalized
      {};

Circle::~Circle() = default;

Point3d Circle::get_point(double t) const {
    // Formula: P(t) = C + R * ( cos(t) * U + sin(t) * V )
    // Where U is _axis_x and V is _axis_y
    // Counterclockwise rotation

    const auto cos{std::cos(t)};
    const auto sin{std::sin(t)};

    const auto offset_u_without_radius{_axis_x * cos}; // cos(t) * U
    const auto offset_v_without_radius{_axis_y * sin}; // sin(t) * V

    const auto offset_without_radius{offset_u_without_radius + offset_v_without_radius};

    return math::translate(_center, offset_without_radius * _radius);
}

Vector3d Circle::get_first_derivative(double t) const {
    // Formula: P'(t) = R * (cos(t) * V - sin(t) * U)
    // Where U is _axis_x and V is _axis_y

    const auto cos{std::cos(t)};
    const auto sin{std::sin(t)};

    const auto offset_v_without_radius{_axis_y * cos}; // cos(t) * V
    const auto offset_u_without_radius{_axis_x * sin}; // sin(t) * U

    const auto offset_without_radius{offset_v_without_radius - offset_u_without_radius};
    return offset_without_radius * _radius;
}

} // namespace model3d
} // namespace curves