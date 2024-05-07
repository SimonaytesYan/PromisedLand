#pragma once

#include "../Utils/GraphicPrimitives.hpp"

enum class EventType 
{
    // PHYSICAL EVENTS
    TICK,
    MOUSE_CLICK,
    MOUSE_MOVE,

    // VIRTUAL EVENTS
    SELECT_BUILDING_EVENT,
    RESOURCES_CHANGED_EVENT,
    BUILD_CELL_EVENT,
    DESTROY_CELL_LOGIC_EVENT,
    DESTROY_CELL_VIEW_EVENT,
    NEW_CITIZEN_EVENT,
    REBUILD_EVENT,
    TRY_BUILD_EVENT,
    COEFF_CHANGED,
    SUCCESSFUL_CELL_VIEW_DELETE,
};

struct Event 
{
    explicit Event(const EventType _event_type)
      : event_type (_event_type)
    {}

    virtual ~Event() = default;

    EventType event_type;
};

struct MouseClickEvent : public Event
{
    MouseClickEvent(Point pos)
    : Event(EventType::MOUSE_CLICK),
      pos (pos)
    { }

    Point pos;
};

struct MouseMoveEvent : public Event
{
    MouseMoveEvent(Point pos)
    : Event(EventType::MOUSE_MOVE),
      pos (pos)
    { }

    Point pos;
};

struct TryBuildEvent : public Event
{
  explicit TryBuildEvent(const size_t index, const Point position)
    : Event    (EventType::TRY_BUILD_EVENT),
      index    (index),
      position (position)
    {}

  size_t index;
  Point  position; 
};