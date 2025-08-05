#include "control/turret/gimbal/field_gimbal/field_gimbal.hpp"
#include "test/mock/rail/rail_turret_mocks.hpp"
#include <gmock/gmock.h>

namespace fang::turret::fieldGimbalTest
{
    // Constructs common FieldGimbal for testing with checker references
    class Setup 
    {
    public:
        using PitchSystemMock = testing::NiceMock<IFieldPitchSystemMock>;
        using YawSystemMock = testing::NiceMock<IFieldYawSystemMock>;

        Setup():
            pitchSystem_{*(new PitchSystemMock{})},
            yawSystem_{*(new YawSystemMock{})},
            fieldGimbal_
            {
                drivers,
                std::unique_ptr<IFieldPitchSystem>(&pitchSystem_),
                std::unique_ptr<IFieldYawSystem>(&yawSystem_)
            }
        {
        }

        Drivers drivers{};
        PitchSystemMock& pitchSystem_;
        YawSystemMock& yawSystem_;
        FieldGimbal fieldGimbal_;
    };
}