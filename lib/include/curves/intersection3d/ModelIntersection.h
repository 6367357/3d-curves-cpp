#ifndef __ModelIntersection_h__
#define __ModelIntersection_h__

#include "curves/math/Constants.h"

namespace curves {

namespace math {
template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
class Point;

} // namespace math

namespace model3d {
class Helix;
class Circle;
} // namespace model3d

namespace intersection3d {

using Point3d = math::Point<double, 3>;

std::vector<Point3d> get_intersection(const model3d::Helix& helix, const model3d::Circle& circle, double precision = math::precision);
std::vector<Point3d> get_intersection(const model3d::Circle& circle, const model3d::Helix& helix, double precision = math::precision);

} // namespace intersection3d
} // namespace curves

#endif // __ModelIntersection_h__