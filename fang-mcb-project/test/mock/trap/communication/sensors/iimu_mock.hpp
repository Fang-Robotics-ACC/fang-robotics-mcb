#ifndef TEST_MOCK_TRAP_COMMUNICATION_SENSORS_TEST_IIMU_MOCK_HPP
#define TEST_MOCK_TRAP_COMMUNICATION_SENSORS_TEST_IIMU_MOCK_HPP
#include "wrap/trap/communication/sensors/iimu.hpp"

#include <gmock/gmock.h>

namespace trap::communication::sensors
{
    class IImuMock : public IImu
    {
    public:
        MOCK_METHOD(Radians, getPitch, (), (const, override));
        MOCK_METHOD(Radians, getYaw, (), (const, override));
        MOCK_METHOD(Radians, getRoll, (), (const, override));
    };
}

#endif 

