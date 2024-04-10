#pragma once

#include "../GameLogic/Tiles/Cell.hpp"
#include "../Events/Eventable.hpp"
#include "../Interlayers/ResourceBarInterlayer.hpp"
#include "../../StlVector/Src/Vector.hpp"

class ResourceManager
{
public:
    explicit ResourceManager(ResourceBarInterlayer& _res_bar_int)
      : user_res                (kStartResources),
        tick_income             (),
        resource_bar_interlayer (_res_bar_int)
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
        // printf("RES: %d\n", user_res.food);
        informResourceBar();
    }

    void onBuild(const Cell* new_cell)
    {
        user_res    += new_cell->getAppearIncome();
        tick_income += new_cell->getTickIncome();

        informResourceBar();
    }

    void onDelete(const Cell* delete_cell)
    {
        // To be continued
    }

    Resources getUserRes()
    {
        return user_res;
    }

private:

    void informResourceBar()
    {
        ResourceEvent res_event(user_res);
        resource_bar_interlayer.pushToView(&res_event);
    }

private:
    Resources              user_res;
    Resources              tick_income;
    ResourceBarInterlayer& resource_bar_interlayer;
};