#ifndef FANG_ROBOTICS_MCB_GEARBOX_REPEAT_ULTRA_MK2_MOCK_HPP
#define FANG_ROBOTICS_MCB_GEARBOX_REPEAT_ULTRA_MK2_MOCK_HPP
#include "motor/gearboxrepeatultramk2.hpp"

#include "wrap/units/units_alias.hpp"

#include "tap/drivers.hpp"
#include "tap/util_macros.hpp"
#include "gmock/gmock.h"

namespace mock
{
    namespace motor
    {
        class GearboxRepeatUltraMk2Mock : virtual public ::motor::GearboxRepeatUltraMk2
        {
        public:
            using ::motor::GearboxRepeatUltraMk2::GearboxRepeatUltraMk2;
            virtual ~GearboxRepeatUltraMk2Mock() = default;

            MOCK_METHOD(void, setTargetSpeed, (const RPM& speed), (override));
            MOCK_METHOD(RPM, getTargetSpeed, (), (const, override));
    		MOCK_METHOD(void, setMaxSpeed, (const RPM& maxSpeed), (override));
    		MOCK_METHOD(RPM, getMaxSpeed, (), (const, override));
    		MOCK_METHOD(void, setMinSpeed, (const RPM& minSpeed), (override));
    		MOCK_METHOD(RPM, getMinSpeed, (), (const, override));
       };//class GearboxRepeatUltraMk2Mock
    }//namespace motor
}//namespace mock
#endif