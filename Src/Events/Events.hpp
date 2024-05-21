#pragma once

#include "../Utils/GraphicPrimitives.hpp"
#include "../GameLogic/Resources.hpp"
#include "../GameLogic/Tiles/Cell.hpp"

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
    COEFF_CHANGED,
    SUCCESSFUL_CELL_VIEW_DELETE,
    MAP_MOVED,
    SMALL_MAP_CHANGED,
    SMALL_MAP_MOVED,

    EVENT_CNT,
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

struct CoeffChangedEvent : public Event 
{
  explicit CoeffChangedEvent(const size_t _index, long int _cur_workers, long int _max_workers)
    : Event       (EventType::COEFF_CHANGED),
      index       (_index),
      cur_workers (_cur_workers),
      max_workers (_max_workers)
    {}

  size_t   index;
  long int cur_workers;
  long int max_workers;
};

struct SuccessfulCellDeleteEvent : public Event
{
  explicit SuccessfulCellDeleteEvent()
    : Event (EventType::SUCCESSFUL_CELL_VIEW_DELETE)
    {}
};

struct MapMovedEvent : public Event
{
  explicit MapMovedEvent(const int _delta_x, const int _delta_y)
    : Event   (EventType::MAP_MOVED),
      delta_x (_delta_x),
      delta_y (_delta_y)
  {}

  int delta_x;
  int delta_y;
};

struct SmallMapMovedEvent : public Event
{
  explicit SmallMapMovedEvent(const Point new_pos)
    : Event   (EventType::SMALL_MAP_MOVED),
      new_pos (new_pos)
  {}

  const Point new_pos;
};

struct SmallMapChangedEvent : public Event
{
  explicit SmallMapChangedEvent(const FieldType field_type, const Point pos)
    : Event   (EventType::SMALL_MAP_CHANGED),
      field_type (field_type),
      pos        (pos)
  {}

  const FieldType field_type;
  const Point     pos;
};