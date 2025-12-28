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
T are_perpendicular(const Vector<T, Dim>& first, const Vector<T, Dim>& second, double tolerance) {
    return std::abs(scalar_product<T, Dim>(first, second)) <= tolerance;
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
bool equal(const CoordStorage<T, Dim>& first, const CoordStorage<T, Dim>& second, double tolerance) {
    for (std::size_t i{}; i < Dim; ++i) {
        if (std::abs(first.data()[i] - second.data()[i]) > tolerance) {
            return false;
        }
    }
    return true;
}

} // namespace math
} // namespace curves