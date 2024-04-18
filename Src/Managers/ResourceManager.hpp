#pragma once

#include <vector>

#include "../GameLogic/Tiles/Cell.hpp"
#include "../Events/Eventable.hpp"
#include "../Interlayers/ResourceBarInterlayer.hpp"

class ResourceManager
{
private:

    struct BuildingProperties
    {
        const Building* ptr;
        Resources needed_res;
        Resources tick_income;
    };

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

        calculateOnBuildResources(building_cell);

        informResourceBar();
    }

    void onDelete(const Cell* delete_cell)
    {
        const Building* building_cell = dynamic_cast<const Building*>(delete_cell);
        if (!building_cell) return; // it is not a Building

        calculateOnDeleteResources(building_cell);

        informResourceBar();
    }

    Resources getUserRes() const
    {
        return user_res;
    }

    bool hasLost() const
    {
        return user_res < kZeroResources;
    }

private:

    void informResourceBar()
    {
        resource_bar_interlayer.pushToView(new ResourceEvent(user_res));
    }

    void calculateOnBuildResources(const Building* building_cell)
    {
        // calculating on build resources
        Resources appear_res = building_cell->getAppearIncome();
        Resources result_res = user_res + appear_res;
        Resources needed_res = Resources::absNegative(result_res);  // ресурсы < 0 => * -1. Остальные - ноль
                                                                    // ресурсы, которых недостаточно
        user_res += (appear_res + needed_res);

        calculateBuildTickResources(appear_res, needed_res, building_cell);
    }

    void calculateBuildTickResources(const Resources appear_res, const Resources needed_res, const Building* building_cell)
    {
        double free_population = static_cast<double>((appear_res * -1 - needed_res).free_population);
        double need_population = static_cast<double>(appear_res.free_population * -1);
        double effectiveness_coeff = free_population / need_population;

        Resources building_tick_income = building_cell->getTickIncome() * effectiveness_coeff;
        tick_income += building_tick_income;

        buildings.push_back({building_cell, needed_res, building_tick_income});
    }

    void calculateOnDeleteResources(const Building* delete_building)
    {
        // calculating on destroy resources
        const auto building_it = findBuildingByPtr(delete_building);    // iterator from vector
        if (building_it == buildings.end()) return;                     // building not found

        Resources destroy_res = delete_building->getDestroyIncome();
        Resources needed_res  = (*building_it).needed_res;

        user_res    += (destroy_res - needed_res);
        tick_income -= (*building_it).tick_income;

        buildings.erase(building_it);
    }

    std::vector<BuildingProperties>::iterator findBuildingByPtr(const Building* building)
    {
              auto it     = buildings.begin();
        const auto end_it = buildings.end();

        for (; it != end_it; ++it)
        {
            if ((*it).ptr == building)
            {
                return it;
            }
        }

        return it;
    }

private:
    Resources              user_res;
    Resources              tick_income;
    ResourceBarInterlayer& resource_bar_interlayer;

    // "Resources" parameter needed to save resources 
    // that are needed for building
    // default: Resources()
    std::vector<BuildingProperties> buildings;
};