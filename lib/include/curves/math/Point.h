#ifndef __Point_h__
#define __Point_h__

#include "CoordStorage.h"

namespace curves {
namespace math {

template <typename T, std::size_t Dim>
    requires std::is_arithmetic_v<T>
class Point : public CoordStorage<T, Dim> {
public:
    using CoordStorage<T, Dim>::CoordStorage;
};

} // namespace math
} // namespace curves

#endif // __Point_h__