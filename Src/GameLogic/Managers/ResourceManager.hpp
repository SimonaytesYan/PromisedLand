#pragma once

#include "../Logics/Tiles/Cell.hpp"
#include "LogicManager.hpp"
#include "../../../StlVector/Src/VectorDecor.hpp"
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

    }

    void pushToView(const Event* event)
    {

    }

    void addCell(Cell* cell)
    {
        cells.PushBack(cell);
    }

    ~ResourceManager()
    {
        STLVectorDecor<Cell*> vector_traits(cells);
        for (auto val : vector_traits)
        {
            delete val;
        }
    }

private:
    Vector<Cell*> cells;
    Resources     user_res;
};