//#ifndef FANG_ROBOTICS_MCB_CONTROL_AMMO_BOOSTER_HPP
//#define FANG_ROBOTICS_MCB_CONTROL_AMMO_BOOSTER_HPP
//#include "wrap/rail/rail_turret_aliases.hpp"
//#include "configuration/wrap/units/units_alias.hpp"
//#include "driver/drivers.hpp"
//namespace control::turret
//{
//    /**
//     * Manages two flywheels. Update must been called periodically.
//     */
//    class AmmoBoosterSystem:
//        virtual public ISimpleAmmoBoosterSubsystemControl
//    {
//    public:
//    struct Config
//    {
//        MetersPerSecond ammoVelocity;
//        FlywheelSystem::Config leftFlywheelConfig;
//        FlywheelSystem::Config rightFlywheelConfig;
//    };
//        AmmoBoosterSystem(Drivers& drivers, const Config& config);
//        void boostOn();
//        void boostOff();
//
//        void setAmmoVelocity(const MetersPerSecond& velocity);
//        void update();
//        void initialize();
//    private:
//        void setRimSpeeds(const MetersPerSecond& velocity);
//        MetersPerSecond m_ammoVelocity;
//        FlywheelSystem m_leftFlywheel;
//        FlywheelSystem m_rightFlywheel;
//
//        static constexpr MetersPerSecond k_stillSpeed{0};
//
//    };
//}
//#endif
//*/