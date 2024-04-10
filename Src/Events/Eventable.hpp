#pragma once

enum class EventType 
{
    // PHYSICAL EVENTS
    TICK,
    MOUSE_CLICK,

    // VIRTUAL EVENTS
};

struct Event 
{
    explicit Event(const EventType _event_type)
      : event_type (_event_type)
    {}

    EventType event_type;
};

struct Eventable 
{
    virtual void push(const Event* event) = 0;
};