#include "wrap/rail/telemetry/itelemetry.hpp"
#include "rail/mock/telemetry/itelemetry_mock.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace ITelemetryTest 
{
    TEST(railTelemetry, compilation)
    {
        // Check for inheritance and compilation
        class Derp : public ::rail::telemetry::ITelemetry<double>
        {
        public:
            double getData() const override {return 10;}
        };

        Derp derp{};
        derp.getData();

        // Check for testing compilation
        constexpr double kExpectedReturn{10.0};
        ::rail::telemetry::ITelemetryMock<double> test{};
        ON_CALL(test, getData).WillByDefault(testing::Return(kExpectedReturn));
        EXPECT_EQ(test.getData(),kExpectedReturn);
    }
}