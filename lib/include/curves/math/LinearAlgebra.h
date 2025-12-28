#ifndef __LinearAlgebra_h__
#define __LinearAlgebra_h__

#include "curves/math/Constants.h"
#include "curves/math/Point.h"
#include "curves/math/Vector.h"

namespace curves {
namespace math {

template <typename T, std::size_t Dim>
    requires(Dim == 3)
Vector<T, Dim> cross_product(const Vector<T, Dim>& first, const Vector<T, Dim>& second);

template <typename T, std::size_t Dim>
T scalar_product(const Vector<T, Dim>& first, const Vector<T, Dim>& second);

template <typename T, std::size_t Dim>
T are_perpendicular(const Vector<T, Dim>& first, const Vector<T, Dim>& second, double tolerance = math::sqr_tolerance);

template <typename T, std::size_t Dim>
Point<T, Dim> translate(const Point<T, Dim>& point, const Vector<T, Dim>& vector);

template <typename T, std::size_t Dim>
bool equal(
    const CoordStorage<T, Dim>& first, const CoordStorage<T, Dim>& second, double tolerance = math::sqr_tolerance);

} // namespace math
} // namespace curves

#include "curves/math/LinearAlgebra.hpp"

#endif // __LinearAlgebra_h__