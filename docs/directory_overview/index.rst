Directory Overview
==================

fang-mcb is sorted into various folders under src:

* Communication: deals with various protocols such as uart, gpio, pwm, etc.
* Control: Controlling high level components such as chassis drivers, turret HALs etc.
* Driver: Device interfaces for various components such as referee serial, dji motors, custom motors, etc.
* Robot: The classes for each unique robot as well as the general class for all robots.
* System: This deals with lower level utilies such as error handling, error communication, and whatnot.
* Util: Miscellaneous catagory for useful mathematical, physics, time utilities, and more.
* Wrap: Wrappers for various libraries such as taproot (traproot), RAIL, and more.



..toctree::
    :glob:

    */index
