#pragma once
#include "proxy_turret_input.hpp"
#include "communication/cool_protocol/janky_float_handler.hpp"
namespace fang::turret
{
    class BasicProxyTurretInputUpdater
    {
    public:
        BasicProxyTurretInputUpdater(ProxyTurretInput& turretInput, communication::JankyFloatHandler& floatHandler);

        void update();

    private:
        ProxyTurretInput turretInput_;
        communication::JankyFloatHandler floatHandler_;
    };
}