#pragma once

#include "../Events/Eventable.hpp"

struct LogicInterlayer 
{
    virtual void pushToView(const EventPtr event) = 0;
};