#pragma once

#include <vector>

#include "../Logics/Tiles/Cell.hpp"
#include "LogicManager.hpp"
#include "../Events/ResourceEvent.hpp"
// #include "../../../StlVector/Src/VectorDecor.hpp"
#include "ViewManager.hpp"

class ResourceManager : public ViewManager, public LogicManager
{
public:
    explicit ResourceManager()
      : cells    (),
        user_res (kStartResources)
    {}

    // Non-copyable
    ResourceManager(const ResourceManager& other)           = delete;
    ResourceManager operator=(const ResourceManager& other) = delete;

    // Non-movable
    ResourceManager(ResourceManager&& other)           = delete;
    ResourceManager operator=(ResourceManager&& other) = delete;

    void pushToLogic(const Event* event)
    {
        const ResourceEvent* res_event = static_cast<const ResourceEvent*>(event);
        
        switch (res_event->event_type)
        {
        case EventType::TICK:
            onTick();
            break;
        case EventType::MOUSE_CLICK:
            user_res += res_event->add_resources;
            break;
        default:
            break;
        }
    }

    void pushToView(const Event* event)
    {

    }

    void addCell(Cell* cell)
    {
        cells.push_back(cell);
    }

    Resources getUserRes()
    {
        return user_res;
    }

    ~ResourceManager()
    {
        // STLVectorDecor<Cell*> vector_traits(cells);
        for (auto val : cells)
        {
            delete val;
        }
    }

private:

    void onTick()
    {
        // STLVectorDecor<Cell*> vector_traits(cells);
        for (auto val : cells)
        {
            user_res += val->getTickIncome();
        }
    }

private:
    std::vector<Cell*> cells;
    Resources          user_res;
};