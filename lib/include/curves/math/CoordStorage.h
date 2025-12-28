#ifndef __CoordStorage_h__
#define __CoordStorage_h__

namespace curves {
namespace math {

template <typename T, std::size_t Dim>
class CoordStorage {
public:
    CoordStorage() = default;
    explicit CoordStorage(T x, T y, T z)
        requires(Dim == 3);
    explicit CoordStorage(std::array<T, Dim> data);

    CoordStorage(const CoordStorage<T, Dim>& other) = default;
    CoordStorage(CoordStorage<T, Dim>&& other) = default;
    CoordStorage<T, Dim>& operator=(const CoordStorage<T, Dim>& other) = default;
    CoordStorage<T, Dim>& operator=(CoordStorage<T, Dim>&& other) = default;
    ~CoordStorage() = default;

    // GET/SET
    const std::array<T, Dim>& data() const;
    std::array<T, Dim>& data();

    const T& x() const
        requires(Dim >= 1);
    T& x()
        requires(Dim >= 1);

    const T& y() const
        requires(Dim >= 2);
    T& y()
        requires(Dim >= 2);

    const T& z() const
        requires(Dim >= 3);
    T& z()
        requires(Dim >= 3);

protected:
    std::array<T, Dim> _data;
};

template <typename T, std::size_t Dim>
    requires requires(std::ostream& os, const T& v) { os << v; }
std::ostream& operator<<(std::ostream& os, const CoordStorage<T, Dim>& p);

} // namespace math
} // namespace curves

#include "CoordStorage.hpp"

#endif // __CoordStorage_h__