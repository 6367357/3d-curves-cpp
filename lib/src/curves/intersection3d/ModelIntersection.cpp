#include "curves/intersection3d/ModelIntersection.h"

#include "curves/math/Constants.h"
#include "curves/math/LinearAlgebra.h"
#include "curves/math/Point.h"
#include "curves/model3d/Circle.h"
#include "curves/model3d/Helix.h"

namespace curves {
namespace intersection3d {

namespace {

std::optional<std::vector<Point3d>> get_intersection_circle_and_helix_collinear_axis(
    const model3d::Helix& helix, const model3d::Circle& circle, double precision) {
    const double sqr_precision{precision * precision};
    if (math::cross_product(helix.get_axis(), circle.get_axis()).get_sqr_magnitude() > sqr_precision) {
        return std::nullopt;
    }

    const double height_from_helix_center{
        math::scalar_product(circle.get_center() - helix.get_center(), helix.get_axis())};
    const double helix_parameter{height_from_helix_center * math::two_pi / helix.get_step()}; // step * t / 2Pi = height

    const auto helix_point{helix.get_point(helix_parameter)};

    if (circle.belongs(helix_point, precision)) {
        return std::vector<Point3d>{helix_point};
    }

    return std::vector<Point3d>{};
}

} // namespace

std::vector<Point3d> get_intersection(const model3d::Helix& helix, const model3d::Circle& circle, double precision) {
    if (const auto& intersection_opt{get_intersection_circle_and_helix_collinear_axis(helix, circle, precision)}) {
        return *intersection_opt;
    }

    // Currently, intersection for non-collinear axes is not implemented or in development
    return {};
}

std::vector<Point3d> get_intersection(const model3d::Circle& circle, const model3d::Helix& helix, double precision) {
    return get_intersection(helix, circle, precision);
}

} // namespace intersection3d
} // namespace curves