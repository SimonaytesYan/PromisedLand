#pragma once

#include <vector>

#include "Eventable.hpp"
#include "Events.hpp"

class EventManager : public Eventable
{
public:

    EventManager()
      : children   (),
        priorities (static_cast<size_t>(EventType::EVENT_CNT), 0)
    {}

    void push(const EventPtr event) override
    {
        const size_t event_type = static_cast<size_t>(event->event_type);
        for (const auto child : children)
        {
            if (child->getPriority() >= priorities[event_type]) 
            {
                child->push(event);
            }
        }
    }

    void setPriority(std::vector<EventType>& event_types, const int new_priority)
    {
        for (const auto event_type : event_types)
        {
            setPriority(event_type, new_priority);
        }
    }

    void privatizeAll(const int new_priority) {
        for (auto& prior : priorities)
        {
            prior = new_priority;
        }
    }

    void setPriority(const EventType event_type, const int new_priority)
    {
        priorities[static_cast<size_t>(event_type)] = new_priority;
    }

    void addChild(Eventable* child)
    {
        children.push_back(child);
    }

    void removeChild(const Eventable* child)
    {
        const auto child_it = std::find(children.begin(), children.end(), child);
        
        if (child_it != children.end())
        {
            children.erase(child_it);
        }
    }

    void resetPriorities()
    {
        for (auto& prior : priorities)
        {
            prior = 0;
        }
    }

private:
    std::vector<Eventable*> children;
    std::vector<int>        priorities;
};