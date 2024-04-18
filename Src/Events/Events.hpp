#pragma once

#include "../Utils/GraphicPrimitives.hpp"
#include "../GameLogic/Resources.hpp"

class CellView;

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

struct CreateCellViewEvent : public Event
{
  explicit CreateCellViewEvent(const FieldType cell_type, const Point pos)
    : Event     (EventType::BUILD_CELL_EVENT),
      cell_type (cell_type),
      pos       (pos)
    {}
  FieldType cell_type;
  Point     pos;
};

struct DestroyCellLogicEvent : public Event
{
  explicit DestroyCellLogicEvent(size_t index_in_vector)
    : Event     (EventType::DESTROY_CELL_LOGIC_EVENT),
      index_in_vector (index_in_vector)
    {}

  size_t index_in_vector;
};

struct DestroyCellViewEvent : public Event
{
  explicit DestroyCellViewEvent(CellView* _cell_view)
    : Event     (EventType::DESTROY_CELL_VIEW_EVENT),
      cell_view (_cell_view)
    {}

  CellView* cell_view;
};

struct NewCitizensEvent : public Event
{
  explicit NewCitizensEvent(const long int citizen_cnt)
    : Event    (EventType::NEW_CITIZEN_EVENT),
      citizens (citizen_cnt)
    {}

  long int citizens;
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

struct RebuildEvent : public Event
{
  explicit RebuildEvent(const size_t index, const FieldType field_type)
    : Event     (EventType::REBUILD_EVENT),
      index     (index),
      cell_type (field_type)
    {}

  size_t    index;
  FieldType cell_type;
};
