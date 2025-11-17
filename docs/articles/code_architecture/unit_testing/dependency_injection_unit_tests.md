Unit Testing with Dependency Injection
--------------------------------------

Unit testing comes with unique challenges when Dependency Injection is utilized. 
In Fang Robotics MCB, we use gmock and gtest in order to set up tests. One of 
the unique challenges is being able to check whether or not a test class has 
been properly called after construction.

One method is to use EXPECT\_CALL before passing the dependencies into the class 
which use them. Unfortunately, in complicated classes, this would require 
building the class each time it is made. To avoid macros, a class which creates 
the testing variable which can be inerited by other classes which will use the 
protected variables and inherit from testing::ParamaterizedTest<> or 
testing::Test.

(Note that it is ill-advised to use protected; however, unit tests should be 
simple with regular classes anyways.

This is the standard template for Fang MCB tests which involved classes that are 
passed through std::unique\_ptr.

**The test directory contains older styles of test. This is the more recent 
style.**

This file is located in: 
fang-robotics-mcb/fang-mcb-project/test/control/chassis/drive/holonomic/mecanum_drive_test.cpp

/home/rave/Documents/github/fang-robotics-mcb/fang-mcb-project/test/control/chassis/drive/quad_drive/base_quad_drive_test.cpp
```cpp
#include "control/chassis/drive/quad_drive/base_quad_drive/base_quad_drive.hpp"
#include "test/mock/rail/rail_motor_mocks.hpp"
#include "driver/drivers.hpp"

#include <memory>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
```
Notice that gtest and gmock is utilized. testing::NiceMock is used in this case 
to prevent warnings from happening.

```cpp
namespace fang::chassis::quadDriveSubsystemTest
{
```
Sometimes, helper function or fixtures are declared which generic names, in 
order to prevent naming collisions, a custom namepsace is made for each level

```cpp
/**
 * Create a subsystem as well as reference
 * accessors for checking calls to motors
 */
class QuadDriveSubsystemTestSetup
{
public:
    QuadDriveSubsystemTestSetup():
        frontLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
        frontRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
        rearLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
        rearRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},

        //This is needed to gain access into the motor states, only required for testing
        //Otherwise the motor states are inaccessible (unique pointer stuff)
        frontLeftMotor_{*frontLeftMotorPtr_},
        frontRightMotor_{*frontRightMotorPtr_},
        rearLeftMotor_{*rearLeftMotorPtr_},
        rearRightMotor_{*rearRightMotorPtr_},

        quadDriveSubsystem_
        {
            drivers_,
            std::move(frontLeftMotorPtr_),
            std::move(frontRightMotorPtr_),
            std::move(rearLeftMotorPtr_),
            std::move(rearRightMotorPtr_)
        }
    {
    }
private:
    //Prevents dangling references
    //Since these pointers are invalid they should not be accessible to the client
    std::unique_ptr<motor::ISpeedMotorMock> frontLeftMotorPtr_;
    std::unique_ptr<motor::ISpeedMotorMock> frontRightMotorPtr_;
    std::unique_ptr<motor::ISpeedMotorMock> rearLeftMotorPtr_;
    std::unique_ptr<motor::ISpeedMotorMock> rearRightMotorPtr_;
protected:
    motor::ISpeedMotorMock& frontLeftMotor_;
    motor::ISpeedMotorMock& frontRightMotor_;
    motor::ISpeedMotorMock& rearLeftMotor_;
    motor::ISpeedMotorMock& rearRightMotor_;
    BaseQuadDrive quadDriveSubsystem_;

    Drivers drivers_{};
};

```
Thi is the main test setup. Notice that it does NOT inherit from gtest. This 
only sets up the variables which will be used in other tests such as accessing 
the motors.

**In the following excerpts, they will be from the setup class, repeating chunk 
and explaining them. The rest of the file will be explained in depth afterwards. 
If you know how to work with gtest, it should be straightforward.**

```cpp
private:
    //Prevents dangling references
    //Since these pointers are invalid they should not be accessible to the client
    std::unique_ptr<motor::ISpeedMotorMock> frontLeftMotorPtr_;
    std::unique_ptr<motor::ISpeedMotorMock> frontRightMotorPtr_;
    std::unique_ptr<motor::ISpeedMotorMock> rearLeftMotorPtr_;
    std::unique_ptr<motor::ISpeedMotorMock> rearRightMotorPtr_;
protected:
    motor::ISpeedMotorMock& frontLeftMotor_;
    motor::ISpeedMotorMock& frontRightMotor_;
    motor::ISpeedMotorMock& rearLeftMotor_;
    motor::ISpeedMotorMock& rearRightMotor_;
    BaseQuadDrive quadDriveSubsystem_;
```
This section is the most important part of the class. Notice that there are 
references to the to the actual motor mocks, which can be used for.

In the client tests, it was noted that it was useful to know whether or not it 
was a fixture class or not.

The private classes initialize the actual instances. These instances will be 
**moved into the client class's constructor (quadDriveSubsystem_)** After they 
are moved, they are inaccessible.

However, for a test to work, these variables still need to be accessed. Note 
that as this is a test environment, it is a non-standard use of the class.

The workaround that was devised was to provide the references (under 
protected:). They remain valid well after the original unique pointers are 
moved. In production, this is **slightly dangerous** as it is intended to bypass 
the point of dependency injection and information hiding. (The client manages 
the motors themselves, no one else).

```cpp
/**
* Create a subsystem as well as reference
* accessors for checking calls to motors
*/
class QuadDriveSubsystemTestSetup
{
public:
    QuadDriveSubsystemTestSetup():
        frontLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
        frontRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
        rearLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
        rearRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},

        //This is needed to gain access into the motor states, only required for testing
        //Otherwise the motor states are inaccessible (unique pointer stuff)
        frontLeftMotor_{*frontLeftMotorPtr_},
        frontRightMotor_{*frontRightMotorPtr_},
        rearLeftMotor_{*rearLeftMotorPtr_},
        rearRightMotor_{*rearRightMotorPtr_},

        quadDriveSubsystem_
        {
            drivers_,
            std::move(frontLeftMotorPtr_),
            std::move(frontRightMotorPtr_),
            std::move(rearLeftMotorPtr_),
            std::move(rearRightMotorPtr_)
        }
    {
    }
```

There will be excerpts from the constructor. This is where a bulk of the 
variable initialization is done. In fang-mcb, uniform bracket initialization is 
the preferred method for initializing all variables.

```cpp
frontLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
frontRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
rearLeftMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
rearRightMotorPtr_{std::make_unique<motor::ISpeedMotorMock>()},
```
First, std::make\_unique initilizes the original smart pointers with actual 
variable information. This is preferred over new because it is exception safe.

```cpp
frontLeftMotor_{*frontLeftMotorPtr_},
frontRightMotor_{*frontRightMotorPtr_},
rearLeftMotor_{*rearLeftMotorPtr_},
rearRightMotor_{*rearRightMotorPtr_},
```
The references are then initialized. Note that these are **not** pointers, so 
the dereference operator has to be applied to the smart pointers, so that they 
return the actual object, not the address of the object. These will remain valid 
for the lifetime of the quadDriveSubsystem_, which is tied to the fixture 
itself.

```cpp
quadDriveSubsystem_
{
    drivers_,
    std::move(frontLeftMotorPtr_),
    std::move(frontRightMotorPtr_),
    std::move(rearLeftMotorPtr_),
    std::move(rearRightMotorPtr_)
}
```
The quadDriveSubsystem_ takes in a drivers, which isn't as important as the 
dependency injection. std::move() is used to convert the smart pointers to an 
r-reference, which means that the responsibility is moved to 
quadDrivdeSubsystem_ on freeing the memory or not. It also gains ownership and 
sole access to these pointers.

```cpp
class QuadDriveSubsystemTest:
    public QuadDriveSubsystemTestSetup,
    public ::testing::Test
{
};
```
This class uses the variables provided by the setup class. Since it inherits 
from Test, it can be used in TEST\_T in gtest.

```
struct WheelSpeedSetterParam
{
    QuadRPM targetWheelSpeeds;
};
class WheelSpeedSetter:
    virtual public QuadDriveSubsystemTestSetup,
    virtual public ::testing::TestWithParam<WheelSpeedSetterParam>
{
protected:
    WheelSpeedSetterParam param{GetParam()};
    QuadRPM targetWheelSpeeds_{param.targetWheelSpeeds};
};
```
This class is a parameterized test. Other tutorials use std::tuple<> but that is 
cumbersome and has a lack of the context for the meaning of the values (earlier 
tests would have comments). Structs were the suitable solution for this.

```cpp
TEST_P(WheelSpeedSetter, setMotorSpeeds)
{
    //Make sure the right wheel speeds are set
    EXPECT_CALL(frontLeftMotor_, setTargetSpeed(targetWheelSpeeds_.frontLeft));
    EXPECT_CALL(frontRightMotor_, setTargetSpeed(targetWheelSpeeds_.frontRight));
    EXPECT_CALL(rearLeftMotor_, setTargetSpeed(targetWheelSpeeds_.rearLeft));
    EXPECT_CALL(rearRightMotor_, setTargetSpeed(targetWheelSpeeds_.rearRight));
    quadDriveSubsystem_.setTargetWheelSpeeds(targetWheelSpeeds_);
}

INSTANTIATE_TEST_CASE_P
(
    zero,
    WheelSpeedSetter,
    ::testing::Values
    (
        WheelSpeedSetterParam{{0_rpm, 0_rpm, 0_rpm, 0_rpm}}
    )
);

INSTANTIATE_TEST_CASE_P
(
    positiveOnly,
    WheelSpeedSetter,
    ::testing::Values
    (
        WheelSpeedSetterParam{{12_rpm, 234_rpm, 345345.2_rpm, 435_rpm}},
        WheelSpeedSetterParam{{1_rpm, 1_rpm, 2_rpm, 4_rpm}}
    )
);

INSTANTIATE_TEST_CASE_P
(
    negativeOnly,
    WheelSpeedSetter,
    ::testing::Values
    (
        WheelSpeedSetterParam{{-12_rpm, -234_rpm, -345345.2_rpm, -435_rpm}},
        WheelSpeedSetterParam{{-1_rpm, -1_rpm, -2_rpm, -4_rpm}}
    )
);

INSTANTIATE_TEST_CASE_P
(
    mixed,
    WheelSpeedSetter,
    ::testing::Values
    (
        WheelSpeedSetterParam{{-12.345345_rpm, 234_rpm, -345345.2_rpm, 435.345_rpm}},
        WheelSpeedSetterParam{{-1_rpm, -345345_rpm, 2_rpm, -4_rpm}}
    )
);

```
These are just instantiation of the paramterized tests. They should use 
designators as shown below:

```cpp
Struct derp
    {
        .derp1 = 12,
        .derp2 = 23
    }
```

The following is the instantiation of the test fixture.

```cpp
//All motors should be initialized and updated on
TEST_F(QuadDriveSubsystemTest, initialize)
{
    EXPECT_CALL(frontLeftMotor_, initialize);
    EXPECT_CALL(frontRightMotor_, initialize);
    EXPECT_CALL(rearLeftMotor_, initialize);
    EXPECT_CALL(rearRightMotor_, initialize);
    quadDriveSubsystem_.initialize();
}

//All motors should be initialized and updated on
TEST_F(QuadDriveSubsystemTest, update)
{
    EXPECT_CALL(frontLeftMotor_, update);
    EXPECT_CALL(frontRightMotor_, update);
    EXPECT_CALL(rearLeftMotor_, update);
    EXPECT_CALL(rearRightMotor_, update);
    quadDriveSubsystem_.refresh();
}
```
This uses QuadDriveSubsystemTest. Notice how it checks for the call of each 
motor **BEFORE** quadDriveSubsystem_ has refresh() called.

```cpp
}
```
Namespace bracket close :D
