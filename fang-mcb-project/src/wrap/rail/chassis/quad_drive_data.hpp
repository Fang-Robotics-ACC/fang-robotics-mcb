#ifndef FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_QUAD_DRIVE_DATA_HPP
#define FANG_ROBOTICS_MCB_WRAP_RAIL_CHASSIS_QUAD_DRIVE_DATA_HPP
#include "rail/chassis/quad_drive_data.hpp"
namespace fang::chassis
{
    template <typename Data>
    using QuadDriveData = rail::chassis::QuadDriveData<Data>;

    template <class Data>
    QuadDriveData<Data> operator*(const QuadDriveData<Data>& quad, double scale)
    {
        return
        QuadDriveData<Data>
        {
            .frontLeft  = quad.frontLeft  * scale,
            .frontRight = quad.frontRight * scale,
            .rearLeft   = quad.rearLeft   * scale,
            .rearRight  = quad.rearRight  * scale
        };
    }

    template <class Data>
    QuadDriveData<Data> operator*(double scale, const QuadDriveData<Data>& quad)
    {
        return quad * scale;
    }
}
#endif