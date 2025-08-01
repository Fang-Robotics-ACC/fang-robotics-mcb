#pragma once
namespace fang::algorithm
{
    /**
     * This was initially made as a universal interface for classes
     * which provide a constant to scale things by.
     * 
     * Chassis power management is often one of the iconic challenges
     * of RMNA. Most algorithms employed utilize providing a scaling constant
     */
    class IScaler
    {
        virtual double getScale() const = 0;
    };
}