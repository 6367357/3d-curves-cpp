#include "curves/model3d/CurveFactory.h"

#include "curves/math/Constants.h"
#include "curves/math/Point.h"
#include "curves/math/Vector.h"
#include "curves/model3d/Circle.h"
#include "curves/model3d/Ellipse.h"
#include "curves/model3d/Helix.h"

namespace curves {
namespace model3d {

std::shared_ptr<Curve> CurveFactory::create_random_curve(bool log_error) {
    return create_random_curve_by_type(random_curve_type(), log_error);
}

std::shared_ptr<Curve> CurveFactory::create_random_curve_by_type(Curve_type curve_type, bool log_error) {
    switch (curve_type) {
    case Curve_type::circle: {
        return create_random_circle(log_error);
    }
    case Curve_type::ellipse: {
        return create_random_ellipse(log_error);
    }
    case Curve_type::helix: {
        return create_random_helix(log_error);
    }
    default: {
        return nullptr;
    }
    }
}

std::shared_ptr<Circle> CurveFactory::create_circle(
    const Point3d& center, double radius, const Vector3d& plane_normal, bool log_error) {
    const auto& start_direction_opt{plane_normal.get_any_perpendicular()};
    if (!start_direction_opt.has_value()) {
        if (log_error) {
            std::cout << "Error: Failed to obtain start direction.\n";
        }
        return nullptr;
    }
    const auto& start_direction{*start_direction_opt};

    return create_circle(center, radius, plane_normal, start_direction, log_error);
}

std::shared_ptr<Circle> CurveFactory::create_circle(const Point3d& center,
    double radius,
    const Vector3d& plane_normal,
    const Vector3d& start_direction,
    bool log_error) {

    // From a mathematical point of view, the radius can be zero (degenerate case: the circle collapses to a point),
    // but in this context a zero or negative radius is considered invalid.
    if (radius <= math::tolerance) {
        if (log_error) {
            std::cout << "Error: Invalid radius: " << radius << '\n';
        }
        return nullptr;
    }

    auto normalized_plane_normal{plane_normal};
    if (!normalized_plane_normal.normalize()) {
        if (log_error) {
            std::cout << "Error: Invalid plane_normal: " << plane_normal << '\n';
        }
        return nullptr;
    }

    auto normalized_start_direction{start_direction};
    if (!normalized_start_direction.normalize()) {
        if (log_error) {
            std::cout << "Error: Invalid start_direction: " << start_direction << '\n';
        }
        return nullptr;
    }

    if (!math::are_perpendicular(normalized_plane_normal, normalized_start_direction)) {
        if (log_error) {
            std::cout << "Error: The plane_normal and the start direction must be perpendicular.\n";
        }
        return nullptr;
    }

    return std::shared_ptr<Circle>{new Circle(center, radius, normalized_plane_normal, normalized_start_direction)};
}

std::shared_ptr<Circle> CurveFactory::create_random_circle(bool log_error) {
    constexpr auto min_radius{math::tolerance};
    constexpr auto max_radius{999999.9};

    const auto center{random_point()};
    const auto radius{random_double(min_radius, max_radius)};
    const auto plane_normal{random_vector()};
    return create_circle(center, radius, plane_normal, log_error);
}

std::shared_ptr<Ellipse> CurveFactory::create_ellipse(
    const Point3d& center, double radius_major, double radius_minor, const Vector3d& plane_normal, bool log_error) {
    const auto& major_direction_opt{plane_normal.get_any_perpendicular()};
    if (!major_direction_opt.has_value()) {
        if (log_error) {
            std::cout << "Error: Failed to obtain major_direction.\n";
        }
        return nullptr;
    }
    const auto& major_direction{*major_direction_opt};

    return create_ellipse(center, radius_major, radius_minor, plane_normal, major_direction, log_error);
}

std::shared_ptr<Ellipse> CurveFactory::create_ellipse(const Point3d& center,
    double radius_major,
    double radius_minor,
    const Vector3d& plane_normal,
    const Vector3d& major_direction,
    bool log_error) {
    // From a mathematical point of view, one or both semi-axes may be zero
    // (degenerate cases: the ellipse collapses to a line segment or a point).
    // However, in this context zero or negative semi-axis values are considered invalid.
    if (radius_major <= math::tolerance || radius_minor <= math::tolerance) {
        if (log_error) {
            std::cout << "Error: Invalid semi-axis lengths: " << radius_major << " : " << radius_minor << '\n';
        }
        return nullptr;
    }

    auto normalized_plane_normal{plane_normal};
    if (!normalized_plane_normal.normalize()) {
        if (log_error) {
            std::cout << "Error: Invalid plane_normal: " << plane_normal << '\n';
        }
        return nullptr;
    }

    auto normalized_major_direction{major_direction};
    if (!normalized_major_direction.normalize()) {
        if (log_error) {
            std::cout << "Error: Invalid major_direction: " << major_direction << '\n';
        }
        return nullptr;
    }

    if (!math::are_perpendicular(normalized_plane_normal, normalized_major_direction)) {
        if (log_error) {
            std::cout << "Error: The plane_normal and the major_direction must be perpendicular.\n";
        }
        return nullptr;
    }

    return std::shared_ptr<Ellipse>{
        new Ellipse(center, radius_major, radius_minor, normalized_plane_normal, normalized_major_direction)};
}

std::shared_ptr<Ellipse> CurveFactory::create_random_ellipse(bool log_error) {
    constexpr auto min_radius{math::tolerance};
    constexpr auto max_radius{999999.9};

    const auto center{random_point()};
    const auto radius_major{random_double(min_radius, max_radius)};
    const auto radius_minor{random_double(min_radius, max_radius)};
    const auto plane_normal{random_vector()};
    return create_ellipse(center, radius_major, radius_minor, plane_normal, log_error);
}

std::shared_ptr<Helix> CurveFactory::create_helix(const Point3d& center, double radius, double step, bool log_error) {

    return create_helix(center, radius, step, Vector3d{0.0, 0.0, 1.0}, log_error);
}

std::shared_ptr<Helix> CurveFactory::create_helix(
    const Point3d& center, double radius, double step, const Vector3d& axis, bool log_error) {
    const auto& start_direction_opt{axis.get_any_perpendicular()};
    if (!start_direction_opt.has_value()) {
        if (log_error) {
            std::cout << "Error: Failed to obtain start direction.\n";
        }
        return nullptr;
    }
    const auto& start_direction{*start_direction_opt};

    return create_helix(center, radius, step, axis, start_direction, log_error);
}

std::shared_ptr<Helix> CurveFactory::create_helix(const Point3d& center,
    double radius,
    double step,
    const Vector3d& axis,
    const Vector3d& start_direction,
    bool log_error) {
    // From a mathematical point of view, the radius or step could be zero
    // (degenerate case: the helix collapses to a straight line along the axis or a single point).
    // However, in this context zero or negative values are considered invalid.
    if (radius <= math::tolerance || step <= math::tolerance) {
        if (log_error) {
            std::cout << "Error: Invalid helix parameters: radius = " << radius << ", step = " << step << '\n';
        }
        return nullptr;
    }

    auto normalized_axis{axis};
    if (!normalized_axis.normalize()) {
        if (log_error) {
            std::cout << "Error: Invalid axis: " << axis << '\n';
        }
        return nullptr;
    }

    auto normalized_start_direction{start_direction};
    if (!normalized_start_direction.normalize()) {
        if (log_error) {
            std::cout << "Error: Invalid start_direction: " << start_direction << '\n';
        }
        return nullptr;
    }

    return std::shared_ptr<Helix>{new Helix(center, radius, step, normalized_axis, normalized_start_direction)};
}

std::shared_ptr<Helix> CurveFactory::create_random_helix(bool log_error) {
    constexpr auto min_radius{math::tolerance};
    constexpr auto max_radius{999999.9};
    constexpr auto min_step{math::tolerance};
    constexpr auto max_step{4999.9};

    const auto center{random_point()};
    const auto radius{random_double(min_radius, max_radius)};
    const auto step{random_double(min_step, max_step)};
    const auto axis{random_vector()};

    return create_helix(center, radius, step, axis, log_error);
}

double CurveFactory::random_double(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(random_generator);
}

Point3d CurveFactory::random_point() {
    constexpr double min_coord{-999999.0};
    constexpr double max_coord{999999.0};

    return Point3d{
        random_double(min_coord, max_coord), random_double(min_coord, max_coord), random_double(min_coord, max_coord)};
}

Vector3d CurveFactory::random_vector() {
    constexpr double min_coord{-999999.0};
    constexpr double max_coord{999999.0};

    return Vector3d{
        random_double(min_coord, max_coord), random_double(min_coord, max_coord), random_double(min_coord, max_coord)};
}

CurveFactory::Curve_type CurveFactory::random_curve_type() {
    std::uniform_int_distribution<int> dist(0, static_cast<int>(Curve_type::size) - 1);
    return static_cast<Curve_type>(dist(random_generator));
}

} // namespace model3d
} // namespace curves