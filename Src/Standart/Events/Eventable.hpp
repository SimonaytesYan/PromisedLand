#pragma once

#include "EventPtr.hpp"

struct Eventable 
{
    virtual void push(const EventPtr event) = 0;
};