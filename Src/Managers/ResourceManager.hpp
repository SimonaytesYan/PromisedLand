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
        // calculating on build resources
        Resources appear_res = building_cell->getAppearIncome();
        Resources result_res = user_res + appear_res;
        Resources needed_res = Resources::absNegative(result_res);  // resources < 0 => * -1. else - zero
        // printf("RESULT RES: %ld %ld\n", result_res.food, result_res.free_population);

        user_res += (appear_res + needed_res);

        calculateBuildTickResources(appear_res, needed_res, building_cell);
    }

    void calculateBuildTickResources(const Resources appear_res, const Resources needed_res, const Building* building_cell)
    {
        printf("BUILD START: %ld %ld %ld %ld\n", appear_res.food, appear_res.free_population, needed_res.food, needed_res.free_population);

        double free_population = static_cast<double>((appear_res * -1 - needed_res).free_population);
        double need_population = static_cast<double>(appear_res.free_population * -1);
        double effectiveness_coeff = free_population / need_population;

        Resources building_tick_income = building_cell->getTickIncome() * effectiveness_coeff;
        tick_income += building_tick_income;

        printf("BUILD END: %lf %lf %lf\n", free_population, need_population, effectiveness_coeff);

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

    void recalcNewCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        const long int new_workers = std::min(building.needed_res.free_population, available_pop);

        user_res.free_population -= new_workers;
        tick_income              -= building.tick_income;

        // recalculating tick_income for building
        double max_population      = building.ptr->getAppearIncome().free_population * -1;
        double current_workers     = max_population - building.needed_res.free_population;
        double future_workers      = new_workers + current_workers;
        double effectiveness_coeff = future_workers / max_population;

        building.tick_income = building.ptr->getTickIncome() * effectiveness_coeff;
        tick_income += building.tick_income;

        // printf("END ADD: %lf MAX_POP%lf FUT%lf %lf %ld %ld\n", effectiveness_coeff, max_population, future_workers, current_workers, available_pop, building.tick_income.food);

        available_pop                       -= new_workers;
        building.needed_res.free_population -= new_workers;
    }

    void recalcLeaveCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        // printf("START: %ld\n", available_pop);
        tick_income -= building.tick_income;

        long int max_population  = building.ptr->getAppearIncome().free_population * -1;
        long int current_workers = max_population - building.needed_res.free_population;

        double left_workers        = std::min(current_workers, available_pop);
        double future_workers      = current_workers - left_workers;
        double effectiveness_coeff = future_workers / max_population;

        // recalculating tick_income for building
        building.tick_income = building.ptr->getTickIncome() * effectiveness_coeff;
        tick_income += building.tick_income;

        available_pop                       -= left_workers;
        building.needed_res.free_population += left_workers;
        // printf("END: %lf %lf %lf %ld %ld %ld\n", effectiveness_coeff, left_workers, future_workers, current_workers, available_pop, building.tick_income.food);
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