#ifndef FANG_ROBOTICS_MCB_TRAP_MOCK_DJI_GM_6020_HPP
#define FANG_ROBOTICS_MCB_TRAP_MOCK_DJI_GM_6020_HPP
#include "trap/motor/dji_motor_aliases.hpp"
#include "trap/motor/dji_gm6020.hpp"
namespace trap
{
    namespace mock
    {
        namespace motor
        {
            class DjiGM6020Mock : virtual public trap::motor::DjiGM6020
            {
            public:
                using DjiSpeedPid = trap::motor::DjiSpeedPid;
                using DjiMotorOutput = trap::motor::DjiMotorOutput;
                using trap::motor::DjiGM6020::DjiGM6020;
                virtual ~DjiGM6020Mock() = default;
                MOCK_METHOD(void, update, (), (override));
    		    MOCK_METHOD(void, setTargetPosition, (const Radians& position), (override));
                MOCK_METHOD(Radians, getPosition, (), (const, override));
                MOCK_METHOD(void, initialize, (), (override));
                MOCK_METHOD(void, setDesiredOutput, (DjiMotorOutput desiredOutput), (override));
                MOCK_METHOD(bool, isMotorOnline, (), (const, override));
                MOCK_METHOD(Celsius, getTemperature, (), (const, override));
                MOCK_METHOD(tap::can::CanBus, getCanBus, (), (const, override));
                MOCK_METHOD(const char*, getName, (), (const, override));
            };
        }
    }
}
#endif
