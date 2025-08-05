#pragma once
#include "rail/chassis/quad_drive_data.hpp"
namespace fang::chassis
{
    /**
     * This can be used for motors and whatnot since
     * it doesn't have operator overloades
     */
    template <typename Element> 
    using QuadCollection = rail::chassis::QuadDriveData<Element>;
    
}