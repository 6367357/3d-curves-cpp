#ifndef __CurveFactory_h__
#define __CurveFactory_h__

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

class Curve;
class Circle;
class Ellipse;
class Helix;

class CurveFactory {
public:
    enum class Curve_type { circle, ellipse, helix, size };

    static std::shared_ptr<Curve> create_random_curve(bool log_error = false);
    static std::shared_ptr<Curve> create_random_curve_by_type(Curve_type curve_type, bool log_error = false);

    // Circle
    static std::shared_ptr<Circle> create_circle(
        const Point3d& center, double radius, const Vector3d& plane_normal, bool log_error = false);
    static std::shared_ptr<Circle> create_circle(const Point3d& center,
        double radius,
        const Vector3d& plane_normal,
        const Vector3d& start_direction,
        bool log_error = false);
    static std::shared_ptr<Circle> create_random_circle(bool log_error = false);

    // Ellipse
    static std::shared_ptr<Ellipse> create_ellipse(const Point3d& center,
        double radius_major,
        double radius_minor,
        const Vector3d& plane_normal,
        bool log_error = false);
    static std::shared_ptr<Ellipse> create_ellipse(const Point3d& center,
        double radius_major,
        double radius_minor,
        const Vector3d& plane_normal,
        const Vector3d& major_direction,
        bool log_error = false);
    static std::shared_ptr<Ellipse> create_random_ellipse(bool log_error = false);

    // Helix
    static std::shared_ptr<Helix> create_helix(
        const Point3d& center, double radius, double step, bool log_error = false);
    static std::shared_ptr<Helix> create_helix(
        const Point3d& center, double radius, double step, const Vector3d& axis, bool log_error = false);
    static std::shared_ptr<Helix> create_helix(const Point3d& center,
        double radius,
        double step,
        const Vector3d& axis,
        const Vector3d& start_direction,
        bool log_error = false);
    static std::shared_ptr<Helix> create_random_helix(bool log_error = false);

private:
    // RANDOM
    inline static std::mt19937_64 random_generator{std::random_device{}()};

    static double random_double(double min, double max);
    static Point3d random_point();
    static Vector3d random_vector();
    static Curve_type random_curve_type();
};

} // namespace model3d
} // namespace curves

#endif // __CurveFactory_h__