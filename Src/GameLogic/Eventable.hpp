#pragma once

enum class EventType 
{
    TICK,
    MOUSE_CLICK
};

struct Event 
{
    EventType event_type;
};

struct Eventable 
{
    virtual void push(const Event* event) = 0;
};