#pragma once

#include "basic_proxy_turret_input_updater.hpp"

namespace fang::turret
{
    BasicProxyTurretInputUpdater::BasicProxyTurretInputUpdater(ProxyTurretInput& turretInput, communication::JankyFloatHandler& floatHandler)
        :
        turretInput_{turretInput},
        floatHandler_{floatHandler} 
    {
    }

    void BasicProxyTurretInputUpdater::update()
    {
        turretInput_.setYaw(floatHandler_.getCurrentFloat());
    }
}