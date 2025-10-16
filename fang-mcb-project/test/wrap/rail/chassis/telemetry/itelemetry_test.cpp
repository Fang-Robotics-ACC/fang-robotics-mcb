#include "wrap/rail/telemetry/itelemetry.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace ITelemetryTest 
{
    TEST(railTelemetry, compilation)
    {
        class Derp : public ::rail::telemetry::ITelemetry<double>
        {
        public:
            double getData() const override {return 10;}
        };

        Derp derp{};
        derp.getData();
    }
}