#include <gtest/gtest.h>

#include "curves/math/Constants.h"
#include "curves/math/LinearAlgebra.h"
#include "curves/model3d/CurveFactory.h"
#include "curves/model3d/Helix.h"

namespace curves {
namespace model3d {

class Helix_test : public ::testing::Test {
protected:
    void SetUp() override {
        const Point3d center{5.0, 5.0, 5.0};
        const double radius{10.0};
        const double step{2.0};
        const Vector3d axis{1.0, 0.0, 0.0};
        const Vector3d start_direction{0.0, 1.0, 0.0};
        helix = CurveFactory::create_helix(center, radius, step, axis, start_direction);
    }

    std::shared_ptr<Helix> helix;
};

TEST_F(Helix_test, get_point) {
    EXPECT_NE(helix, nullptr);

    { // 0.0 degrees
        const Point3d calibration_point{5.0, 15.0, 5.0};
        const auto& point{helix->get_point(0.0)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 90.0 degrees
        const Point3d calibration_point{5.5, 5.0, 15.0};
        const auto& point{helix->get_point(math::half_pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 180.0 degrees
        const Point3d calibration_point{6.0, -5.0, 5.0};
        const auto& point{helix->get_point(math::pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 270.0 degrees
        const Point3d calibration_point{6.5, 5.0, -5.0};
        const auto& point{helix->get_point(math::three_pi_over_two)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 360.0 degrees
        const Point3d calibration_point{7.0, 15.0, 5.0};
        const auto& point{helix->get_point(math::two_pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }
}

TEST_F(Helix_test, get_first_derivative) {
    EXPECT_NE(helix, nullptr);
    constexpr double rise_along_x{0.3183098861837906}; // step / 2pi
    { // 0.0 degrees
        const Vector3d calibration_vector{rise_along_x, 0.0, 10.0};
        const auto& vector{helix->get_first_derivative(0.0)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }

    { // 90.0 degrees
        const Vector3d calibration_vector{rise_along_x, -10.0, 0.0};
        const auto& vector{helix->get_first_derivative(math::half_pi)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }

    { // 180.0 degrees
        const Vector3d calibration_vector{rise_along_x, 0.0, -10.0};
        const auto& vector{helix->get_first_derivative(math::pi)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }

    { // 270.0 degrees
        const Vector3d calibration_vector{rise_along_x, 10.0, 0.0};
        const auto& vector{helix->get_first_derivative(math::three_pi_over_two)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }
}

} // namespace model3d
} // namespace curves