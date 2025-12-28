#include "curves/model3d/Helix.h"

#include "curves/math/Constants.h"
#include "curves/math/LinearAlgebra.h"
#include "curves/model3d/Curve.h"

namespace curves {
namespace model3d {

Helix::Helix(const Point3d& center, double radius, double step, const Vector3d& axis, const Vector3d& start_direction)
    : _center{center}, _radius{radius}, _step{step}, _axis{axis}, _axis_x{start_direction},
      _axis_y{math::cross_product(axis, start_direction)} {};

Helix::~Helix() = default;

Point3d Helix::get_point(double t) const {
    // Formula: P(t) = C + R * ( cos(t) * U + sin(t) * V ) + (h * t / 2pi) * N
    // Where U is _axis_x , V is _axis_y and N is _axis
    // Counterclockwise rotation

    const auto cos{std::cos(t)};
    const auto sin{std::sin(t)};

    const auto offset_u_without_radius{_axis_x * cos}; // cos(t) * U
    const auto offset_v_without_radius{_axis_y * sin}; // sin(t) * V
    const auto offset_n{_axis * (_step * t / math::two_pi)}; // (h * t / 2pi) * N

    const auto offset_uv_without_radius{offset_u_without_radius + offset_v_without_radius};
    const auto offset{offset_uv_without_radius * _radius + offset_n};

    return math::translate(_center, offset);
}

Vector3d Helix::get_first_derivative(double t) const {
    // Formula: P'(t) = R * (cos(t) * V - sin(t) * U) + ( h / 2pi) * N
    // Where U is _axis_x , V is _axis_y and N is _axis

    const auto cos{std::cos(t)};
    const auto sin{std::sin(t)};

    const auto offset_v_without_radius{_axis_y * cos}; // cos(t) * V
    const auto offset_u_without_radius{_axis_x * sin}; // sin(t) * U
    const auto offset_uv_without_radius{offset_v_without_radius - offset_u_without_radius};
    const auto offset_n{_axis * (_step / math::two_pi)}; // ( h / 2pi) * N

    return offset_uv_without_radius * _radius + offset_n;
}

} // namespace model3d
} // namespace curves