#include "telemetry/adapter/iangular_velocity_adapter.hpp"

#include "rail/mock/telemetry/iangular_velocity_telemetry_mock.hpp"

#include "wrap/units/units_alias.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace fang::telemetry
{
    TEST(IAngularVelocityAdapter, match)
    {
        rail::telemetry::IAngularVelocityMock<RPM> velocityTelemetry{};
        telemetry::IAngularVelocityAdapter VelocityAdapter{velocityTelemetry};

        const RPM kExpectedVelocity{10};

        ON_CALL(velocityTelemetry, getAngularVelocity()).WillByDefault(testing::Return(kExpectedVelocity));

        EXPECT_EQ(VelocityAdapter.getData(), kExpectedVelocity);
    }
}