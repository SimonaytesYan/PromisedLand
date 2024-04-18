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

    void onNewCitizenArrival(long int citizen_cnt)
    {
        for (auto& building : buildings)
        {
            if (building.needed_res.free_population > 0)
            {
                recalcNewCitizenResources(building, citizen_cnt);
            }

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
            printf("Counter: %ld\n", citizen_cnt);
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

private:

    void informResourceBar()
    {
        // int cnt = 0;
        // for (auto& building : buildings)
        // {
        //     std::cout << cnt++ << "\nNeeded:\n" << building.needed_res << "Tick:\n" << building.tick_income << "\n\n";
        // }
        resource_bar_interlayer.pushToView(new ResourceEvent(user_res));
    }

    void calculateOnBuildResources(const Building* building_cell)
    {
        
    }

    void calculateBuildTickResources(const Resources appear_res, const Resources need_res, const Building* building_cell)
    {
        
    }

    void calculateOnDeleteResources(const Building* delete_building)
    {
        
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
};