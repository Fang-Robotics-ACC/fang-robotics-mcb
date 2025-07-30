#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_RAIL_TURRET_ALIASES_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_RAIL_TURRET_ALIASES_HPP
#include "rail/turret/feeder/isimple_feeder.hpp"
#include "wrap/rail/turret/isimple_feeder_subsystem.hpp" //TODO: Figure out how to incorporate taproot without entaglement
#include <memory>
namespace fang::turret
{
    using ISimpleFeeder = rail::turret::ISimpleFeeder;
    using ISimpleFeederControl = rail::turret::ISimpleFeederControl;
}
#endif