#pragma once

#include "../Events/Eventable.hpp"

struct ViewInterlayer
{
    virtual void pushToLogic(const EventPtr event) {}
};