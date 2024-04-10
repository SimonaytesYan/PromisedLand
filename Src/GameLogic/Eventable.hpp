#pragma once

#include "../Events.hpp"

struct Eventable 
{
    virtual void push(const Event* event) = 0;
};