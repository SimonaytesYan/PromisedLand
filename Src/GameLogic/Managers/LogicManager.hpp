#pragma once

#include "../Eventable.hpp"

struct LogicManager 
{
    virtual void pushToView(const Event* event) = 0;
};