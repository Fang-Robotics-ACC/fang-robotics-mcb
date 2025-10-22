#include "telemetry/adapter/iangular_position_adapter.hpp"

#include "rail/mock/telemetry/iangular_position_telemetry_mock.hpp"

#include "wrap/units/units_alias.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace fang::telemetry
{
    TEST(IAngularPositionAdapter, match)
    {
        rail::telemetry::IAngularPositionMock<Radians> positionTelemetry{};
        telemetry::IAngularPositionAdapter positionAdapter{positionTelemetry};

        const Radians kExpectedRadians{10};

        ON_CALL(positionTelemetry, getAngularPosition()).WillByDefault(testing::Return(kExpectedRadians));

        EXPECT_EQ(positionAdapter.getData(), kExpectedRadians);
    }
}