#pragma once

#include <vector>

#include "Eventable.hpp"
#include "Events.hpp"

class EventManager : public Eventable
{
public:

    EventManager()
      : children   (),
        priorities (static_cast<size_t>(EventType::EVENT_CNT))
    {}

    void push(const EventPtr event) override
    {
        for (const auto child : children)
        {
            
            // if (child->getPriority() >= priorities[])
        }
    }

    // void set

private:
    std::vector<Eventable*> children;
    std::vector<int>        priorities;
};