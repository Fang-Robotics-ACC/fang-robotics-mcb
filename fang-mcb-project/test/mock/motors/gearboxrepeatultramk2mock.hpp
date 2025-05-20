#ifndef FANG_ROBOTICS_MCB_GEARBOX_REPEAT_ULTRA_MK2_MOCK_HPP
#define FANG_ROBOTICS_MCB_GEARBOX_REPEAT_ULTRA_MK2_MOCK_HPP
#include "unitaliases.hpp"
#include "directionality.hpp"
#include "gearboxrepeatultramk2.hpp"

#include "ispeedmotor.h"
#include "tap/drivers.hpp"
#include "tap/util_macros.hpp"
#include "gmock/gmock.h"

namespace mock
{
    namespace motors
    {
        class GearboxRepeatUltraMk2Mock : virtual public ::motors::GearboxRepeatUltraMk2
        {
        public:
            using ::motors::GearboxRepeatUltraMk2::GearboxRepeatUltraMk2;
            virtual ~GearboxRepeatUltraMk2Mock() = default;

    		MOCK_METHOD(void, setSpeed, (const RPM& speed), (override));
    		MOCK_METHOD(RPM, getSpeed, (), (const, override));
    		MOCK_METHOD(void, setMaxSpeed, (const RPM& maxSpeed), (override));
    		MOCK_METHOD(RPM, getMaxSpeed, (), (const, override));
    		MOCK_METHOD(void, setMinSpeed, (const RPM& minSpeed), (override));
    		MOCK_METHOD(RPM, getMinSpeed, (), (const, override));
       };//class GearboxRepeatUltraMk2Mock
    }//namespace motors
}//namespace mock
#endif