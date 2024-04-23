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
        for (auto& building : buildings)
        {
            recalcNewCitizenResources(building, citizen_cnt);

            if (citizen_cnt == 0)
            {
                break;
            }
        }

        informResourceBar();
    }

    void onCitizenLeave(long int citizen_cnt)
    {
        for (auto& building : buildings)
        {
            recalcLeaveCitizenResources(building, citizen_cnt);

            if (citizen_cnt == 0)
            {
                break;
            }
        }

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

        double    efficiency_coeff = 1.0;
        long int  max_workers      = building_cell->getMaxWorkers();

        user_res                 += appear_res;
        user_res.free_population -= max_workers;

        if (max_workers > 0)
        {
            if (user_res.free_population < 0)
            {
                long int worker_overdraft = user_res.free_population * -1;
                user_res.free_population  = 0;

                building_cell->setCurWorkers(max_workers - worker_overdraft);
                efficiency_coeff = static_cast<double>(building_cell->getCurWorkers()) / static_cast<double>(max_workers);
            }
            else 
            {
                // all working slots are occupied
                building_cell->setCurWorkers(max_workers);
            }
        }

        Resources building_tick_income = building_cell->getTickIncome() * efficiency_coeff;
        tick_income += building_tick_income;

        buildings.push_back({building_cell, building_tick_income});
    }

    void calculateOnDeleteResources(const Building* delete_building)
    {
        user_res                 += delete_building->getDestroyIncome();
        user_res.free_population += delete_building->getCurWorkers();

        auto building_it = findBuildingByPtr(delete_building);

        tick_income -= building_it->tick_income;

        buildings.erase(building_it);
    }

    void recalcNewCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        long int max_workers    = building.ptr->getMaxWorkers();
        if (max_workers == 0) return;

        long int cur_workers    = building.ptr->getCurWorkers();
        long int new_workers    = std::min(available_pop, max_workers - cur_workers);
        long int future_workers = cur_workers + new_workers;

        tick_income -= building.tick_income;

        double efficiency_coeff = static_cast<double>(future_workers) / static_cast<double>(max_workers);
        building.tick_income    = building.ptr->getTickIncome() * efficiency_coeff;

        tick_income += building.tick_income;

        building.ptr->setCurWorkers(future_workers);

        available_pop            -= new_workers;
        user_res.free_population -= new_workers;
    }

    void recalcLeaveCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        long int max_workers    = building.ptr->getMaxWorkers();
        if (max_workers == 0) return;
        
        long int cur_workers    = building.ptr->getCurWorkers();
        long int left_workers   = std::min(available_pop, cur_workers);
        long int future_workers = cur_workers - left_workers;

        tick_income -= building.tick_income;


        double efficiency_coeff = static_cast<double>(future_workers) / static_cast<double>(max_workers);
        building.tick_income    = building.ptr->getTickIncome() * efficiency_coeff;

        tick_income += building.tick_income;

        building.ptr->setCurWorkers(future_workers);

        available_pop            -= left_workers;
        user_res.free_population += left_workers;
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