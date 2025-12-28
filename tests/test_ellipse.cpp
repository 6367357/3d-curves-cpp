#include <gtest/gtest.h>

#include "curves/math/Constants.h"
#include "curves/math/LinearAlgebra.h"
#include "curves/model3d/CurveFactory.h"
#include "curves/model3d/Ellipse.h"

namespace curves {
namespace model3d {

class Ellipse_test : public ::testing::Test {
protected:
    void SetUp() override {
        const Point3d center{5.0, 5.0, 5.0};
        const double radius_major{10.0};
        const double radius_minor{8.0};
        const Vector3d plane_normal{1.0, 0.0, 0.0};
        const Vector3d major_direction{0.0, 1.0, 0.0};
        ellipse = CurveFactory::create_ellipse(center, radius_major, radius_minor, plane_normal, major_direction);
    }

    std::shared_ptr<Ellipse> ellipse;
};

TEST_F(Ellipse_test, get_point) {
    EXPECT_NE(ellipse, nullptr);

    { // 0.0 degrees
        const Point3d calibration_point{5.0, 15.0, 5.0};
        const auto& point{ellipse->get_point(0.0)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 90.0 degrees
        const Point3d calibration_point{5.0, 5.0, 13.0};
        const auto& point{ellipse->get_point(math::half_pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 180.0 degrees
        const Point3d calibration_point{5.0, -5.0, 5.0};
        const auto& point{ellipse->get_point(math::pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }

    { // 270.0 degrees
        const Point3d calibration_point{5.0, 5.0, -3.0};
        const auto& point{ellipse->get_point(math::three_pi_over_two)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_tolerance));
    }
}

TEST_F(Ellipse_test, get_first_derivative) {
    EXPECT_NE(ellipse, nullptr);

    { // 0.0 degrees
        const Vector3d calibration_vector{0.0, 0.0, 8.0};
        const auto& vector{ellipse->get_first_derivative(0.0)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }

    { // 90.0 degrees
        const Vector3d calibration_vector{0.0, -10.0, 0.0};
        const auto& vector{ellipse->get_first_derivative(math::half_pi)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }

    { // 180.0 degrees
        const Vector3d calibration_vector{0.0, 0.0, -8.0};
        const auto& vector{ellipse->get_first_derivative(math::pi)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }

    { // 270.0 degrees
        const Vector3d calibration_vector{0.0, 10.0, 0.0};
        const auto& vector{ellipse->get_first_derivative(math::three_pi_over_two)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_tolerance));
    }
}

} // namespace model3d
} // namespace curves