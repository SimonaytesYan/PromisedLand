#pragma once

#include <vector>

#include "../GameLogic/Tiles/Cell.hpp"
#include "../Events/Eventable.hpp"
#include "../Interlayers/ResourceBarInterlayer.hpp"
#include "../GameLogic/Tiles/Building.hpp"
#include "../Events/Events.hpp"
#include "../CellLoader/CellKeeper.hpp"

class ResourceManager
{
private:

    struct BuildingProperties
    {
        Building* ptr;
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

        calculateOnBuildResources(const_cast<Building*>(building_cell));

        informResourceBar();
    }

    void onNewCitizenArrival(long int citizen_cnt)
    {
        informResourceBar();
    }

    void onCitizenLeave(long int citizen_cnt)
    {
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

    bool tryBuild(FieldType building_type)
    {
        return (CellKeeper::getAppearIncome(building_type).wood  * -1) <= user_res.wood &&
               (CellKeeper::getAppearIncome(building_type).stone * -1) <= user_res.stone;
    }

private:

    void informResourceBar()
    {
        resource_bar_interlayer.pushToView(new ResourceEvent(user_res));
    }

    void calculateOnBuildResources(Building* building_cell)
    {
        Resources appear_res = building_cell->getAppearIncome();
        user_res += appear_res;

        Resources building_tick_income = calculateBuildTickResources(building_cell, building_cell->getTickIncome());

        buildings.push_back({building_cell, building_tick_income});
        tryAddHouse(building_cell);
    }

    Resources calculateBuildTickResources(Building* building_cell, Resources default_tick)
    {
        long max_workers = building_cell->getMaxWorkers();
        if (max_workers == 0) 
        {
            tick_income += default_tick;
            return default_tick; 
        }

        long available_workers = user_res.free_population;
        long cur_workers       = std::min(available_workers, building_cell->getMaxWorkers());

        user_res.free_population -= cur_workers;
        building_cell->setCurWorkers(cur_workers);

        double effectiveness_coeff     = static_cast<double>(cur_workers) / static_cast<double>(max_workers);
        Resources building_tick_income = default_tick * effectiveness_coeff;

        tick_income += building_tick_income;

        return building_tick_income;
    }

    void tryAddHouse(Building* building)
    {
        if (building->getFieldType() == static_cast<size_t>(ReservedTypes::HOUSE))
        {
            houses.push_back(building);
        }
    }

    void calculateOnDeleteResources(const Building* delete_building)
    {
        Resources destroy_res = delete_building->getDestroyIncome();
        user_res += destroy_res;

        auto building_it = findBuildingByPtr(delete_building);

        tick_income -= building_it->tick_income;

        calculateDeleteFreePopulation(delete_building);

        buildings.erase(building_it);
        tryDeleteHouse(delete_building);
    }

    void calculateDeleteFreePopulation(const Building* delete_building)
    {
        user_res.free_population += delete_building->getCurWorkers();
    }

    void tryDeleteHouse(const Building* delete_building)
    {
        if (delete_building->getFieldType() == static_cast<size_t>(ReservedTypes::HOUSE))
        {
                  auto it     = houses.begin();
            const auto end_it = houses.end();

            for (; it != end_it; ++it)
            {
                if (*it == delete_building)
                {
                    houses.erase(it);
                    break;
                }
            }
        }
    }

    void recalcNewCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        
    }

    void recalcLeaveCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        
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
    std::vector<Building*>          houses;
};