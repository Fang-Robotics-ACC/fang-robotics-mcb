#pragma once

#include "janky_float_handler.hpp"
#include "cool_serial/idata_handler.hpp"

namespace fang::communication
{
    void JankyFloatHandler::handleData(const coolSerial::Bytes& bytes)
    {
        currentFloat_ = JankyFloat::deserialize(bytes);
    }

    float JankyFloatHandler::getCurrentFloat()
    {
        return currentFloat_;
    }
}