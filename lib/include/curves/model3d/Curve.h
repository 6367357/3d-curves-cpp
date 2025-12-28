#ifndef __Curve_h__
#define __Curve_h__

namespace curves {
namespace math {
template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
class Point;

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
class Vector;
} // namespace math

namespace model3d {

using Point3d = math::Point<double, 3>;
using Vector3d = math::Vector<double, 3>;

class Curve {
public:
    virtual ~Curve() = default;

    virtual Point3d get_point(double t) const = 0;
    virtual Vector3d get_first_derivative(double t) const = 0;
};

} // namespace model3d
} // namespace curves

#endif // __Curve_h__