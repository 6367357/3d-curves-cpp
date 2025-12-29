namespace curves {
namespace math {

template <typename T, std::size_t Dim>
    requires(Dim == 3)
Vector<T, Dim> cross_product(const Vector<T, Dim>& first, const Vector<T, Dim>& second) {
    return Vector<T, Dim>{first.y() * second.z() - first.z() * second.y(),
        first.z() * second.x() - first.x() * second.z(),
        first.x() * second.y() - first.y() * second.x()};
}

template <typename T, std::size_t Dim>
T scalar_product(const Vector<T, Dim>& first, const Vector<T, Dim>& second) {
    T result{};
    for (std::size_t i{}; i < Dim; ++i) {
        result += first.data()[i] * second.data()[i];
    }
    return result;
}

template <typename T, std::size_t Dim>
T are_perpendicular(const Vector<T, Dim>& first, const Vector<T, Dim>& second, double precision) {
    return std::abs(scalar_product<T, Dim>(first, second)) <= precision;
}

template <typename T, std::size_t Dim>
Point<T, Dim> translate(const Point<T, Dim>& point, const Vector<T, Dim>& vector) {
    Point result{point};
    for (std::size_t i{}; i < Dim; ++i) {
        result.data()[i] += vector.data()[i];
    }
    return result;
}

template <typename T, std::size_t Dim>
bool equal(const CoordStorage<T, Dim>& first, const CoordStorage<T, Dim>& second, double precision) {
    for (std::size_t i{}; i < Dim; ++i) {
        if (std::abs(first.data()[i] - second.data()[i]) > precision) {
            return false;
        }
    }
    return true;
}

template <typename T, std::size_t Dim>
Vector<T, Dim> operator-(const Point<T, Dim>& minuend, const Point<T, Dim>& subtrahend) {
    Vector<T, Dim> result{};
    for (std::size_t i{}; i < Dim; ++i) {
        result.data()[i] = minuend.data()[i] - subtrahend.data()[i];
    }
    return result;
}

template <typename T, std::size_t Dim>
bool is_point_on_plane(const Point<T, Dim>& point,
    const Point<T, Dim>& plane_point,
    const Vector<T, Dim>& plane_normal,
    const double precision)
{
    const auto vector_between_points { point - plane_point };
    return std::abs(scalar_product(vector_between_points, plane_normal)) <= precision;
}

template <typename T, std::size_t Dim>
T get_sqr_distance(const Point<T, Dim>& first, const Point<T, Dim>& second)
{
    T result { static_cast<T>(0) };
    for (std::size_t i{}; i < Dim; ++i) {
        result += (second.data()[i] - first.data()[i]) * (second.data()[i] - first.data()[i]); 
    }
    return result;
}

} // namespace math
} // namespace curves