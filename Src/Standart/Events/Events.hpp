#pragma once

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