#pragma once

#include "../GameLogic/Tiles/Cell.hpp"
#include "Eventable.hpp"
#include "../Constants.hpp"

struct CellEvent : public Event
{
    explicit CellEvent(const EventType _event_type, const FieldType _cell_type = FieldType::Error)
      : Event     (_event_type),
        cell_type (_cell_type)
    {}

    FieldType cell_type;
};