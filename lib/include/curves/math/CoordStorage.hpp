namespace curves {
namespace math {

template <typename T, std::size_t Dim>
CoordStorage<T, Dim>::CoordStorage(T x, T y, T z)
    requires(Dim == 3)
{
    _data = {x, y, z};
}

template <typename T, std::size_t Dim>
CoordStorage<T, Dim>::CoordStorage(std::array<T, Dim> data) : _data{std::move(data)} {};

template <typename T, std::size_t Dim>
const std::array<T, Dim>& CoordStorage<T, Dim>::data() const {
    return _data;
}

template <typename T, std::size_t Dim>
std::array<T, Dim>& CoordStorage<T, Dim>::data() {
    return _data;
}

template <typename T, std::size_t Dim>
const T& CoordStorage<T, Dim>::x() const
    requires(Dim >= 1)
{
    return _data[0];
}

template <typename T, std::size_t Dim>
T& CoordStorage<T, Dim>::x()
    requires(Dim >= 1)
{
    return _data[0];
}

template <typename T, std::size_t Dim>
const T& CoordStorage<T, Dim>::y() const
    requires(Dim >= 2)
{
    return _data[1];
}

template <typename T, std::size_t Dim>
T& CoordStorage<T, Dim>::y()
    requires(Dim >= 2)
{
    return _data[1];
}

template <typename T, std::size_t Dim>
const T& CoordStorage<T, Dim>::z() const
    requires(Dim >= 3)
{
    return _data[2];
}

template <typename T, std::size_t Dim>
T& CoordStorage<T, Dim>::z()
    requires(Dim >= 3)
{
    return _data[2];
}

template <typename T, std::size_t Dim>
    requires requires(std::ostream& os, const T& v) { os << v; }
std::ostream& operator<<(std::ostream& os, const CoordStorage<T, Dim>& p) {
    os << '{';
    for (std::size_t i = 0; i < Dim; ++i) {
        if (i > 0)
            os << ", ";
        os << p.data()[i];
    }
    os << '}';
    return os;
}

} // namespace math
} // namespace curves
