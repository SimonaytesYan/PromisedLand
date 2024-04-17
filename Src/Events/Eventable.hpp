#pragma once

#include "Events.hpp"
#include "EventPtr.hpp"
#include "../Utils/GraphicPrimitives.hpp"
#include "../GameLogic/Resources.hpp"

class CellView;

enum class EventType 
{
    // PHYSICAL EVENTS
    TICK,
    MOUSE_CLICK,

    // VIRTUAL EVENTS
    SELECT_BUILDING_EVENT,
    RESOURCES_CHANGED_EVENT,
    BUILD_CELL_EVENT,
    DESTROY_CELL_EVENT,
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

struct BuildCellEvent : public Event
{
  explicit BuildCellEvent(CellView* _cell_view)
    : Event     (EventType::BUILD_CELL_EVENT),
      cell_view (_cell_view)
    {}

  CellView* cell_view;
};

struct DestroyCellEvent : public Event
{
  explicit DestroyCellEvent(CellView* _cell_view)
    : Event     (EventType::DESTROY_CELL_EVENT),
      cell_view (_cell_view)
    {}

  CellView* cell_view;
};

struct Eventable 
{
    virtual void push(const EventPtr event) = 0;
};
