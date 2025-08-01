#include "robot_mecanum_logic.hpp"

#include "units.h"
#include <cassert>

using namespace units::literals;
namespace fang::chassis
{
    RobotMecanumLogic::RobotMecanumLogic(const Config& config):
        RobotMecanumLogic(config.horizontalWheelDistance,
                          config.verticalWheelDistance,
                          config.wheelRadius)
    {
    }

    RobotMecanumLogic::RobotMecanumLogic(const Meters& horizontalWheelDistance,
                                         const Meters& verticalWheelDistance,
                                         const Meters& wheelRadius):
    kHorizontalWheelDistance_{horizontalWheelDistance},
    kVerticalWheelDistance_{verticalWheelDistance},
    kWheelRadius_{wheelRadius / 1_rad}
    {
        //assert(wheelRadius.to<double>() >= 0.0 && "Wheel radius must be positive");
        //assert(horizontalWheelDistance.to<double>() >= 0.0 && "Chassis dimension must be positive");
        //assert(verticalWheelDistance.to<double>() >= 0.0 && "Chassis dimension must be positive");
    }
    void RobotMecanumLogic::setMotion(const Velocity2D& translation, const RPM& rotation)
    {
        setTranslation(translation);
        setRotation(rotation);
    }
    void RobotMecanumLogic::setTranslation(const Velocity2D& translation)
    {
        translation_ = translation;
    }
    void RobotMecanumLogic::setRotation(const RPM& rotation)
    {
        rotation_ = rotation;
    }
    const Velocity2D& RobotMecanumLogic::getTranslation() const
    {
        return translation_;
    }
    RPM RobotMecanumLogic::getRotation() const
    {
        return rotation_;
    }
    QuadRPM RobotMecanumLogic::getWheelSpeeds() const
    {
        return QuadRPM{getFrontLeftWheelSpeed(), getFrontRightWheelSpeed(),
                             getRearLeftWheelSpeed(),  getRearRightWheelSpeed()};
    }

    RPM RobotMecanumLogic::getFrontLeftWheelSpeed() const
    {
        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 20, but v_x is v_y and v_y is v_x
        //If all of v_x is positive, then the wheels are pushing in the same
        //direction. It is desired for this to be positive
        //How many radius's per second? i.e. radians persecond
        //w_1
        const MetersPerSecond translationFactor{(translation_.y + translation_.x)};
        const MetersPerSecond rotationFactor{kWheelDistanceConstant_ * rotation_};
        return ((1.0 / kWheelRadius_) * (translationFactor - rotationFactor));
    }
    RPM RobotMecanumLogic::getFrontRightWheelSpeed() const
    {
        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 20, but v_x is v_y and v_y is v_x
        //If all of v_x is positive, then the wheels are pushing in the same
        //direction. It is desired for this to be positive
        //w_2
        const MetersPerSecond translationFactor{(translation_.y - translation_.x).to<double>()};
        const MetersPerSecond rotationFactor{kWheelDistanceConstant_ * rotation_};
        return ((1.0 / kWheelRadius_) * (translationFactor + rotationFactor));
    }
    RPM RobotMecanumLogic::getRearLeftWheelSpeed() const
    {
        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 20, but v_x is v_y and v_y is v_x
        //If all of v_x is positive, then the wheels are pushing in the same
        //direction. It is desired for this to be positive
        //w_3
        const MetersPerSecond translationFactor{(translation_.y - translation_.x).to<double>()};
        const MetersPerSecond rotationFactor{kWheelDistanceConstant_ * rotation_};
        return ((1.0 / kWheelRadius_) * (translationFactor - rotationFactor));
    }
    RPM RobotMecanumLogic::getRearRightWheelSpeed() const
    {
        //https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
        //Equation 20, but v_x is v_y and v_y is v_x
        //Equation 20, but v_x is v_y and v_y is v_x
        //If all of v_x is positive, then the wheels are pushing in the same
        //direction. It is desired for this to be positive
        //w_4
        const MetersPerSecond translationFactor{(translation_.y + translation_.x).to<double>()};
        const MetersPerSecond rotationFactor{kWheelDistanceConstant_ * rotation_};
        return ((1.0 / kWheelRadius_) * (translationFactor + rotationFactor));
    }
}