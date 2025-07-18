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

#ifndef DRIVERS_HPP_
#define DRIVERS_HPP_
#include "tap/drivers.hpp"
#include "control/input_handler.hpp"

class Drivers : public tap::Drivers
{
    friend class DriversSingleton;

#ifdef ENV_UNIT_TESTS
public:
#endif
    Drivers() : tap::Drivers{} {}

    //prevent copying
    Drivers(const Drivers&) = delete;
    Drivers& operator=(Drivers&) = delete;

public:
    control::InputHandler inputHandler{remote};
    void initializeIo();
    void update();
    void updateIo();
    /**
     * These are assocated classes that needs to be
     * called at the same interval as the motors are updated
     * (command scheduler should not spam)
     */
    void motorTimeoutUpdate();

};  // class Drivers
#endif  // DRIVERS_HPP_
