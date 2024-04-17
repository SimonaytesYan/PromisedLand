#pragma once

#include <vector>

#include "../GameLogic/Tiles/Cell.hpp"
#include "../Events/Eventable.hpp"
#include "../Interlayers/ResourceBarInterlayer.hpp"

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
        informResourceBar();
    }

    void onBuild(const Cell* new_cell)
    {
        const Building* building_cell = dynamic_cast<const Building*>(new_cell);
        if (!building_cell) return; // it is not a Building

        calculateResources(building_cell);

        informResourceBar();
    }

    void onDelete(const Cell* delete_cell)
    {
        const Building* building_cell = dynamic_cast<const Building*>(delete_cell);
        if (!building_cell) return; // it is not a Building

        user_res    += building_cell->getDestroyIncome();
        tick_income -= building_cell->getTickIncome();

        informResourceBar();
    }

    Resources getUserRes()
    {
        return user_res;
    }

    bool hasLost()
    {
        return user_res < kZeroResources;
    }

private:

    void informResourceBar()
    {
        ResourceEvent res_event(user_res);
        resource_bar_interlayer.pushToView(&res_event);
    }

    void calculateResources(const Building* building_cell)
    {
        // calculating on build resources
        Resources appear_res = building_cell->getAppearIncome();
        Resources result_res = user_res + appear_res;
        Resources needed_res = Resources::absNegative(result_res);
        
        user_res += (appear_res + needed_res);

        buildings.push_back({building_cell, needed_res});
        // calculating on tick resources
        double effectiveness_coeff = (appear_res * -1 - needed_res).free_population / (-1 * appear_res.free_population);
        printf("LOOK RES: %ld %ld %lf\n", appear_res.free_population, needed_res.free_population, effectiveness_coeff);
        Resources tick_resources   = building_cell->getTickIncome() * effectiveness_coeff;
        tick_income += tick_resources;
    }

    void calculateTickResources(const Building* building_cell)
    {
        tick_income += building_cell->getTickIncome();
    }

private:
    Resources              user_res;
    Resources              tick_income;
    ResourceBarInterlayer& resource_bar_interlayer;

    // "Resources" parameter needed to save resources 
    // that are needed for building
    // default: Resources()
    std::vector<std::pair<const Building*, Resources>> buildings;
};