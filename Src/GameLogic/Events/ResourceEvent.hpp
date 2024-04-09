#pragma once

#include "../Eventable.hpp"
#include "../Logics/Resources.hpp"

struct ResourceEvent : public Event
{
    explicit ResourceEvent(const EventType _event_type, const Resources _resources)
      : Event         (_event_type),
        add_resources (_resources)
    {}

    Resources add_resources;
};