#pragma once

#include "EventPtr.hpp"

struct Eventable 
{
    virtual void push(const EventPtr event) = 0;

    virtual void setPriority(const int _priority)
    {
        priority = _priority;
    }

    virtual int getPriority()
    {
        return priority;
    }

private:
    int priority = 0;
};
