#pragma once

#include "../Events/ResourceEvent.hpp"s
#include "ResourceManager.hpp"
#include "ViewManager.hpp"

class WindowViewManager : public ViewManager
{
public:

    explicit WindowViewManager(ResourceManager& _res_manager)
      : res_manager (_res_manager)
    {}

    void pushToLogic(const Event* event) override
    {
        ResourceEvent res_event(event->event_type);
        res_manager.pushToLogic(&res_event);
    }

private:
    ResourceManager& res_manager;
};