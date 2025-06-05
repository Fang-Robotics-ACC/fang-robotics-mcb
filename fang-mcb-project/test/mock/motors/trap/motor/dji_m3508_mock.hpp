
#include "wrap/trap/motor/dji_motor_aliases.hpp"
#include "trap/motor/dji_m3508.hpp"
namespace trap
{
    namespace mock
    {
        namespace motor
        {
            class DjiM3508Mock : virtual public trap::motor::DjiM3508
            {
            public:
                using DjiSpeedPid = trap::motor::DjiSpeedPid;
                using DjiMotorOutput = trap::motor::DjiMotorOutput;
                struct Config
                {
                    tap::motor::MotorId motorId;
                    tap::can::CanBus canBus;
                    const char* name;
                    bool inverted;
                    double gearRatio;
                    DjiSpeedPid speedPidConfig;
                };
                using trap::motor::DjiM3508::DjiM3508;
                virtual ~DjiM3508Mock() = default;
                MOCK_METHOD(void, update, (), (override));
    		    MOCK_METHOD(void, setTargetSpeed, (const RPM& speed), (override));
                MOCK_METHOD(RPM, getSpeed, (), (const, override));
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