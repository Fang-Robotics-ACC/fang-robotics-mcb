#pragma once

#include "rail/telemetry/itelemetry.hpp"

namespace fang::telemetry
{
    template <typename DataType>
    using ITelemetry = rail::telemetry::ITelemetry<DataType>;
}