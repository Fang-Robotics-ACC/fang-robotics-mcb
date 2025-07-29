#ifndef FANG_ROBOTICS_MCB_CONTROL_CHASSS_DRIVE_QUAD_DRIVE_DATA_QUAD_INDEX_HPP
#define FANG_ROBOTICS_MCB_CONTROL_CHASSS_DRIVE_QUAD_DRIVE_DATA_QUAD_INDEX_HPP
namespace fang::chassis
{        
    /**
     * Useful for when quad data or motors are stored in an array
     * and it is required to access them by index
     */
    enum class QuadIndex
    {
        frontLeft = 0,
        frontRight,
        rearLeft,
        rearRight
    };
}
#endif