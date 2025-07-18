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
#ifndef DRIVERS_SINGLETON_HPP_
#define DRIVERS_SINGLETON_HPP_

#ifndef ENV_UNIT_TESTS

#include "drivers.hpp"
/**
 * Class that allows one to construct a Drivers instance because of frienship
 * with the Drivers class.
 */
class DriversSingleton
{
public:
    static Drivers drivers;

    /**
     * @return The singleton instance of the Drivers class. This is the only instance of the
     *      Drivers class that should be created anywhere in the non-unit test framework.
     * @note I don't like unecessary pointers. Derferencing the drivers pointer and passing
     *      it as a reference twice will cause a crash for some reason.
     *      It is likely that you will never have to use this. There are only two files you
     *      should be calling this function from -- `main.cpp` and `*_control.cpp`, either to
     *      run I/O stuff and to add a Drivers pointer to an instance of a Subsystem or Command.
     */
    Drivers& getDrivers();
};  // class DriversSingleton


#endif  // DRIVERS_SINGLETON_HPP_
#endif
