#pragma once

#include "../../Standart/Events/Events.hpp"
#include "../Utils/GraphicPrimitives.hpp"
#include "../GameLogic/Resources.hpp"
#include "../GameLogic/Tiles/Cell.hpp"

class CellView;

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