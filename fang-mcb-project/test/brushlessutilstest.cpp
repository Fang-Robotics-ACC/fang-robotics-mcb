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


#include "motor/util/brushlessutils.hpp"
#include "wrap/units/units_alias.hpp"

#include <gtest/gtest.h>

TEST(brushlessUtils , RPMVoltageConversion)
{
    Volts maxVoltage{24.0};
    Volts zeroVoltage {0.0};
    RPM zeroRPM {0.0};
    RPM maxUltraRPM{34800.0};
    RPMPerVolt kv {1450.0};

    EXPECT_DOUBLE_EQ(motor::brushless::controllerVoltageToSpeed(zeroVoltage, kv).to<double>(), zeroRPM.to<double>());
    EXPECT_DOUBLE_EQ(motor::brushless::controllerVoltageToSpeed(maxVoltage, kv).to<double>(), maxUltraRPM.to<double>());

    EXPECT_DOUBLE_EQ(motor::brushless::speedToControllerVoltage(zeroRPM, kv).to<double>(), zeroVoltage.to<double>());
    EXPECT_DOUBLE_EQ(motor::brushless::speedToControllerVoltage(maxUltraRPM, kv).to<double>(), maxVoltage.to<double>());
}