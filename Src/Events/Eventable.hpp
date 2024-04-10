#pragma once

#include "../Utils/GraphicPrimitives.hpp"

enum class EventType 
{
    // PHYSICAL EVENTS
    TICK,
    MOUSE_CLICK,

    // VIRTUAL EVENTS
    SELECT_BUILDING_EVENT,
    RESOURCES_CHANGED_EVENT,
};

struct Event 
{
    explicit Event(const EventType _event_type)
      : event_type (_event_type)
    {}

    EventType event_type;
};

struct MouseEvent : public Event
{
    MouseEvent(Point pos)
    : Event(EventType::MOUSE_CLICK),
      pos (pos)
    { }

    Point pos;
};

struct SelectBuildingEvent : public Event
{
    SelectBuildingEvent(FieldType type)
    : Event(EventType::SELECT_BUILDING_EVENT),
      type (type)
    { }

    FieldType type;
};

struct ResourceEvent : public Event
{
  explicit ResourceEvent(const Resources _resources)
    : Event     (EventType::RESOURCES_CHANGED_EVENT),
      resources (_resources)
    {}

  Resources resources;
};

struct Eventable 
{
    virtual void push(const Event* event) = 0;
};