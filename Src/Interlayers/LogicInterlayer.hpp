#pragma once

#include "../Events/Eventable.hpp"

struct LogicInterlayer 
{
    virtual void pushToView(const Event* event) = 0;
};