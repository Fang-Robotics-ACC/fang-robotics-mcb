#include "control/chassis/drive/holonomic/mecanum/mecanum_drive/mecanum_drive.hpp"

#include "test/mock/trap/algorithms/ramp_mock.hpp"
#include "test/mock/trap/algorithms/ramp_2d_mock.hpp"

#include "wrap/trap/algorithms/ramp_2d.hpp"
#include "wrap/trap/algorithms/ramp.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace fang::chassis
{
    //using namespace units::literals;
    ///**
    // * Create a subsystem as well as reference
    // * accessors for checking calls to motors
    // */
    //class MecanumSubsystemTestMockup
    //{
    //protected:
    //    MecanumSubsystemTestMockup():
    //        //This is needed to gain access into the motor states, only required for testing
    //        //Otherwise the motor states are inaccessible (unique pointer stuff)
    //        quadDrivePtr_{std::make_unique<}



    //        quadDriveSubsystem_
    //    {
    //    }
    //    Drivers drivers_{};
    //private:
    //    //Prevents dangling references
    //    //Since these pointers are invalid they should not be accessible to the client
    //    std::unique_ptr<IQuadDriveSubsystem> quadDrivePtr_;
    //    std::unique_ptr<MecanumSubsystem::Imu> imuPtr_;
    //    std::unique_ptr<MecanumSubsystem::TranslationRamp> translationRampPtr_;
    //    std::unique_ptr<MecanumSubsystem::RotationRamp> rotationRampPtr_;
    //protected:
    //    IQuadDriveSubsystem& quadDrive_;
    //    MecanumSubsystem::Imu& imu_;
    //    MecanumSubsystem::TranslationRamp& translationRamp_;
    //    MecanumSubsystem::RotationRamp& rotationRamp_;

    //    MecanumSubsystem& quadDriveSubsystem_;

    //};


}