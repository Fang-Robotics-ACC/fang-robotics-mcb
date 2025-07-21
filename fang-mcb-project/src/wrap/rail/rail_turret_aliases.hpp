#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_RAIL_TURRET_ALIASES_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_RAIL_TURRET_ALIASES_HPP
#include "rail/turret/feeder/isimple_feeder.hpp"
#include "wrap/rail/turret/i_simple_feeder_subsystem_control.hpp" //TODO: Figure out how to incorporate taproot without entaglement
namespace fang::turret
{
    using ISimpleFeeder = rail::turret::ISimpleFeeder;
    using ISimpleFeederControl = rail::turret::ISimpleFeederControl;
    using ISimpleFeederSubsystemControl = rail::turret::ISimpleFeederSubsystemControl;
}
#endif