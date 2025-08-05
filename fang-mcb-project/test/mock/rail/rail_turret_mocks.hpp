#include "rail/mock/turret/gimbal/ifield_pitch_system_mock.hpp"
#include "rail/mock/turret/gimbal/ifield_yaw_system_mock.hpp"

#include "wrap/units/units_alias.hpp"

namespace fang::turret
{
    using IFieldPitchSystemMock = rail::turret::IFieldYawSystemMock<Radians>;
    using IFieldPitchSystemMock = rail::turret::IFieldPitchSystemMock<Radians>;
}