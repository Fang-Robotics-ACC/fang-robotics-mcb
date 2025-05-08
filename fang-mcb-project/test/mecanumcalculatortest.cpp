#include "gtest/gtest.h"
#include "mecanumcalculator.hpp"
#include "unitaliases.hpp"
#include "quaddrivedata.hpp"
#include "chassislogicaliases.hpp"
#include <iostream>

TEST(mecanumCalculator, MecanumMotionCalculator )
{
    using namespace units::literals;
    logic::chassis::MecanumCalculator calc{1.0_m, 1.0_m, 1.0_m};
    const logic::chassis::QuadDriveData test {1.0_rpm, 1.0_rpm, 1.0_rpm, 1.0_rpm};
    const logic::chassis::Velocity2D expected{0.0_mps, 1.0_mps};
    const RPM expectedRotation{0.0};
    calc.setWheelSpeeds(test);
    EXPECT_DOUBLE_EQ(calc.getTranslation().x.to<double>(), expected.x.to<double>());
    EXPECT_DOUBLE_EQ(calc.getTranslation().y.to<double>(), expected.y.to<double>());
    EXPECT_DOUBLE_EQ(calc.getRotation().to<double>(), expectedRotation.to<double>());
}
