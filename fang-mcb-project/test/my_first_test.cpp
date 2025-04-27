/*
 * Copyright (c) 2020-2021 Fang-Robotics
 *
 * This file is part of fang-mcb.
 *
 * fang-mcb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fang-mcb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fang-mcb.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include "brushlessutils.hpp"
#include "unitaliases.hpp"


TEST(brushlessUtils , RPMVoltageConversion)
{
    Volts voltage{24.0};
    Volts zeroVoltage {0.0};
    RPMPerVolt kv {1450.0};

    //RPM zeroTest {motors::util::brushless::controllerVoltageToSpeed(zeroVoltage, kv)};
    //RPM ultraTest {motors::util::brushless::controllerVoltageToSpeed(voltage, kv)};

    //EXPECT_DOUBLE_EQ(zeroTest.to<double>(), 0.0);
    //EXPECT_DOUBLE_EQ(ultraTest.to<double>(), 34800.0);
}

TEST(brushlessUtils , RPMToVoltage)
{
    RPMPerVolt kv {1450.0};
    RPM zeroRPM{0.0};
    RPM maxUltraRPM{34800.0};

    //Volts zeroRPMTest {motors::util::brushless::speedToControllerVoltage(zeroRPM, kv)};
    //Volts maxRPMTest {motors::util::brushless::speedToControllerVoltage(maxUltraRPM, kv)};
    //EXPECT_DOUBLE_EQ(zeroRPMTest.to<double>(), 0.0);
    //EXPECT_DOUBLE_EQ(maxRPMTest.to<double>(), 0.0);
}