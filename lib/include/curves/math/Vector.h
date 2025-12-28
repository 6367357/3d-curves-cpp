#ifndef __Vector_h__
#define __Vector_h__

#include "CoordStorage.h"

namespace curves {
namespace math {

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
class Vector : public CoordStorage<T, Dim> {
public:
    using CoordStorage<T, Dim>::CoordStorage;

    double get_sqr_magnitude() const;
    double get_magnitude() const;
    std::optional<Vector> get_any_perpendicular() const;

    bool normalize();

    Vector operator/(T scalar) const;
    Vector& operator/=(T scalar);

    Vector operator*(T scalar) const;
    Vector& operator*=(T scalar);

    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);

    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);
};

} // namespace math
} // namespace curves

#include "Vector.hpp"

#endif // __Vector_h__d