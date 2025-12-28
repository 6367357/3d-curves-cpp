#include "curves/math/Point.h"
#include "curves/math/Vector.h"

#include "curves/model3d/Circle.h"
#include "curves/model3d/Curve.h"
#include "curves/model3d/CurveFactory.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <thread>
#include <vector>

using namespace curves;
using namespace curves::math;
using namespace curves::model3d;

using Point3d = Point<double, 3>;
using Vector3d = Vector<double, 3>;

std::vector<std::shared_ptr<Curve>> get_random_curves(std::size_t amount) {
    std::vector<std::shared_ptr<Curve>> result;
    result.reserve(amount);

    std::generate_n(std::back_inserter(result), amount, []() { return CurveFactory::create_random_curve(true); });

    return result;
}

std::vector<std::shared_ptr<Circle>> filter_circles(const std::vector<std::shared_ptr<Curve>>& curves) {
    std::vector<std::shared_ptr<Circle>> result{};

    for (const auto& curve : curves) {
        if (const auto& circle{std::dynamic_pointer_cast<Circle>(curve)}) {
            result.emplace_back(circle);
        }
    }

    return result;
}

void sort_circles_by_radius_safe(std::vector<std::shared_ptr<Circle>>& circles) {
    std::ranges::sort(circles, [](const std::shared_ptr<Circle>& first, const std::shared_ptr<Circle>& second) {
        // Antireflexivity: is performed
        // Antisymmetry: is performed
        // Transitivity: is performed

        if (!first && !second) {
            // Both are nullptr -> considered equal.
            return false;
        }

        if (!first) {
            // first is nullptr, second is not -> nullptr is "less than" any non-null pointer.
            return true;
        }

        if (!second) {
            // first is not nullptr, second is nullptr -> non-null pointer is "greater than" nullptr
            return false;
        }

        return first->get_radius() < second->get_radius();
    });
}

void sort_circles_by_radius(std::vector<std::shared_ptr<Circle>>& circles) {
    std::ranges::sort(circles, [](const std::shared_ptr<Circle>& first, const std::shared_ptr<Circle>& second) {
        return first->get_radius() < second->get_radius();
    });
}

double sum_radii_calculation(const std::vector<std::shared_ptr<Circle>>& circles) {
    constexpr std::size_t min_elements_per_thread{10};

    if (circles.empty()) {
        return 0.0;
    }

    const std::size_t required_number_of_threads{static_cast<std::size_t>(
        std::ceil(static_cast<double>(circles.size()) / static_cast<double>(min_elements_per_thread)))};

    const std::size_t number_of_threads{
        std::min(static_cast<std::size_t>(std::thread::hardware_concurrency()), required_number_of_threads)};

    std::vector<double> partial_sums(number_of_threads, 0.0);
    std::vector<std::thread> threads{};
    threads.reserve(number_of_threads);

    auto worker = [&](std::size_t partial_index) {
        std::size_t start{partial_index * min_elements_per_thread};
        std::size_t end{std::min((partial_index + 1) * min_elements_per_thread, circles.size())}; // circles.size() > 0
        double sum{std::accumulate(
            circles.begin() + start, circles.begin() + end, 0.0, [](double sum, const std::shared_ptr<Circle>& circle) {
                if (!circle) {
                    return sum;
                }
                return sum + circle->get_radius();
            })};
        partial_sums[partial_index] = sum;
    };

    for (std::size_t i{}; i < number_of_threads; ++i) {
        threads.emplace_back(worker, i);
    };

    for (auto& thread : threads) {
        thread.join();
    }

    return std::accumulate(partial_sums.begin(), partial_sums.end(), 0.0);
}

int main() {
    constexpr std::size_t amount_of_curves{2000};

    // - Randomized container: Populate a container with randomly generated curves (random type and parameters).
    const auto& randomized_container{get_random_curves(amount_of_curves)};

    // - Circle filtering: Create a second container containing only circles from the first container (no deep copies).
    auto only_circles{
        filter_circles(randomized_container)}; // It is guaranteed that all circles in only_circles are not nullptr.

    // - Sorting: Sort the second container by circle radii in ascending order.
    sort_circles_by_radius(only_circles);

    // - Sum calculation: Compute the total sum of radii in the second container.
    // - Make radius summation parallel across threads.
    const auto& sum_radii{sum_radii_calculation(only_circles)};

    return 0;
}