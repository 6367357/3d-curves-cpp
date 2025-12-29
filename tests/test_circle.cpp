#include <gtest/gtest.h>

#include "curves/math/Constants.h"
#include "curves/math/LinearAlgebra.h"
#include "curves/model3d/Circle.h"
#include "curves/model3d/CurveFactory.h"

namespace curves {
namespace model3d {

class Circle_test : public ::testing::Test {
protected:
    void SetUp() override {
        const Point3d center{5.0, 5.0, 5.0};
        const double radius{10.0};
        const Vector3d plane_normal{1.0, 0.0, 0.0};
        const Vector3d start_direction{0.0, 1.0, 0.0};
        circle = CurveFactory::create_circle(center, radius, plane_normal, start_direction);
    }

    std::shared_ptr<Circle> circle;
};

TEST_F(Circle_test, get_point) {
    EXPECT_NE(circle, nullptr);

    { // 0.0 degrees
        const Point3d calibration_point{5.0, 15.0, 5.0};
        const auto& point{circle->get_point(0.0)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_precision));
    }

    { // 90.0 degrees
        const Point3d calibration_point{5.0, 5.0, 15.0};
        const auto& point{circle->get_point(math::half_pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_precision));
    }

    { // 180.0 degrees
        const Point3d calibration_point{5.0, -5.0, 5.0};
        const auto& point{circle->get_point(math::pi)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_precision));
    }

    { // 270.0 degrees
        const Point3d calibration_point{5.0, 5.0, -5.0};
        const auto& point{circle->get_point(math::three_pi_over_two)};
        EXPECT_TRUE(math::equal(point, calibration_point, math::sqr_precision));
    }
}

TEST_F(Circle_test, get_first_derivative) {
    EXPECT_NE(circle, nullptr);

    { // 0.0 degrees
        const Vector3d calibration_vector{0.0, 0.0, 10.0};
        const auto& vector{circle->get_first_derivative(0.0)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_precision));
    }

    { // 90.0 degrees
        const Vector3d calibration_vector{0.0, -10.0, 0.0};
        const auto& vector{circle->get_first_derivative(math::half_pi)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_precision));
    }

    { // 180.0 degrees
        const Vector3d calibration_vector{0.0, 0.0, -10.0};
        const auto& vector{circle->get_first_derivative(math::pi)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_precision));
    }

    { // 270.0 degrees
        const Vector3d calibration_vector{0.0, 10.0, 0.0};
        const auto& vector{circle->get_first_derivative(math::three_pi_over_two)};
        EXPECT_TRUE(math::equal(vector, calibration_vector, math::sqr_precision));
    }
}

} // namespace model3d
} // namespace curves
