#pragma once

#include "../Eventable.hpp"

struct ViewInterlayer
{
    virtual void pushToLogic(const Event* event) = 0;
};