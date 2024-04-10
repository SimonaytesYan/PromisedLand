#pragma once

#include "../GameLogic/Tiles/Cell.hpp"
#include "../../StlVector/Src/Vector.hpp"

class ResourceManager
{
public:
    explicit ResourceManager()
      : user_res    (kStartResources),
        tick_income ()
    {}

    // Non-copyable
    ResourceManager(const ResourceManager& other)           = delete;
    ResourceManager operator=(const ResourceManager& other) = delete;

    // Non-movable
    ResourceManager(ResourceManager&& other)           = delete;
    ResourceManager operator=(ResourceManager&& other) = delete;

    void onTick()
    {
        user_res += tick_income;
    }

    void onBuild(const Cell* new_cell)
    {
        user_res    += new_cell->getAppearIncome();
        tick_income += new_cell->getTickIncome();
    }

    Resources getUserRes()
    {
        return user_res;
    }

private:
    Resources     user_res;
    Resources     tick_income;
};