#include "curves/math/Constants.h"
#include "curves/math/LinearAlgebra.h"

namespace curves {
namespace math {

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
double Vector<T, Dim>::get_sqr_magnitude() const {
    double result{0.0};

    for (std::size_t i{}; i < Dim; ++i) {
        result +=
            static_cast<double>(CoordStorage<T, Dim>::_data[i]) * static_cast<double>(CoordStorage<T, Dim>::_data[i]);
    }

    return result;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
double Vector<T, Dim>::get_magnitude() const {
    return std::sqrt(get_sqr_magnitude());
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
std::optional<Vector<T, Dim>> Vector<T, Dim>::get_any_perpendicular() const {
    if (get_sqr_magnitude() <= sqr_tolerance) {
        return std::nullopt;
    }

    if (Dim < 2) {
        return std::nullopt;
    }

    const auto& min_iter{
        std::ranges::min_element(CoordStorage<T, Dim>::_data, {}, [](const T& value) { return std::abs(value); })};
    if (min_iter == CoordStorage<T, Dim>::_data.end()) {
        return std::nullopt;
    }

    std::size_t min_index{static_cast<std::size_t>(std::distance(CoordStorage<T, Dim>::_data.begin(), min_iter))};

    Vector result{};
    result.data()[min_index] = T{static_cast<T>(1)};
    return cross_product(*this, result);
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
bool Vector<T, Dim>::normalize() {
    const auto sqr_magnitude{get_sqr_magnitude()};
    if (sqr_magnitude <= sqr_tolerance) {
        return false;
    }
    const auto magnitude{std::sqrt(sqr_magnitude)};

    *this = *this / magnitude;

    return true;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim> Vector<T, Dim>::operator/(T scalar) const {
    Vector result{*this};
    result /= scalar;
    return result;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim>& Vector<T, Dim>::operator/=(T scalar) {
    for (auto& coord : CoordStorage<T, Dim>::_data) {
        coord /= scalar;
    }
    return *this;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim> Vector<T, Dim>::operator*(T scalar) const {
    Vector result{*this};
    result *= scalar;
    return result;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim>& Vector<T, Dim>::operator*=(T scalar) {
    for (auto& coord : CoordStorage<T, Dim>::_data) {
        coord *= scalar;
    }

    return *this;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim> Vector<T, Dim>::operator+(const Vector<T, Dim>& other) const {
    Vector result{*this};
    result += other;
    return result;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim>& Vector<T, Dim>::operator+=(const Vector<T, Dim>& other) {
    for (std::size_t i{}; i < Dim; ++i) {
        this->data()[i] += other.data()[i];
    }

    return *this;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim> Vector<T, Dim>::operator-(const Vector<T, Dim>& other) const {
    Vector result{*this};
    result -= other;
    return result;
}

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
Vector<T, Dim>& Vector<T, Dim>::operator-=(const Vector<T, Dim>& other) {
    for (std::size_t i{}; i < Dim; ++i) {
        this->data()[i] -= other.data()[i];
    }

    return *this;
}

} // namespace math
} // namespace curves