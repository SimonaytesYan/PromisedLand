#pragma once

#include <vector>

#include "../Interlayers/CellInterlayer.hpp"
#include "../Events/Eventable.hpp"
#include "../Interlayers/ResourceBarInterlayer.hpp"
#include "../GameLogic/Tiles/Building.hpp"
#include "../Events/Events.hpp"
#include "../CellLoader/CellKeeper.hpp"


class ResourceManager
{
    static ResourceManager* current_manager;

private:

    struct BuildingProperties
    {
        BuildingProperties(
            Building* _ptr,
            Resources _cur_tick,
            long int  _cur_workers,
            long int  _max_workers
        )
          : ptr (_ptr),
            tick_income (_cur_tick),
            cur_workers (_cur_workers),
            max_workers (_max_workers)
        {}

        Building* ptr;
        Resources tick_income;

        long int cur_workers;
        long int max_workers;
    };

    struct HouseProperties : public BuildingProperties
    {
        HouseProperties(
            Building* _ptr,
            Resources _cur_tick,
            long int  _cur_workers,
            long int  _max_workers,
            Resources _default_income
        )
          : BuildingProperties  (_ptr, _cur_tick, _cur_workers, _max_workers),
            default_tick_income (_default_income)
        {}

        Resources default_tick_income;
    };

public:
    explicit ResourceManager(ResourceBarInterlayer& _res_bar_int)
      : user_res                (kStartResources),
        tick_income             (),
        resource_bar_interlayer (_res_bar_int)
    {
        ResourceManager::current_manager = this;
    }

    // Non-copyable
    ResourceManager(const ResourceManager& other)           = delete;
    ResourceManager operator=(const ResourceManager& other) = delete;

    // Non-movable
    ResourceManager(ResourceManager&& other)           = delete;
    ResourceManager operator=(ResourceManager&& other) = delete;

    void onTick()
    {
        for (auto house : houses)   // TODO auto&
        {
            Resources house_res = house.ptr->getTickIncome();

            if (house_res.population > 0)
            {
                long int pop = house_res.population;
                onNewCitizen(pop);

                user_res.population      += house_res.population;
                user_res.free_population += pop;

                house.ptr->setCurWorkers(house.ptr->getCurWorkers() + house_res.population);
                house.cur_workers = house.ptr->getCurWorkers();
                recalculateHouseIncome(house);
            }
            else if (house_res.population < 0)
            {
                long int pop = house_res.population * -1;

                if (user_res.free_population >= pop)
                {
                    user_res.population      -= pop;
                    user_res.free_population -= pop;
                }
                else
                {
                    killCitizen(pop);

                    user_res.population      += house_res.population;
                    user_res.free_population -= ((house_res.population * -1) - pop);

                    if (user_res.free_population < 0)
                    {
                        user_res.free_population = 0;
                    }
                }

                house.ptr->setCurWorkers(house.ptr->getCurWorkers() + house_res.population);
                house.cur_workers = house.ptr->getCurWorkers();
                recalculateHouseIncome(house);
            }
        }

        updateCoeffDisplays();

        user_res += tick_income;
        informResourceBar();
    }

    void onBuild(const Cell* new_cell)
    {
        const Building* building_cell = dynamic_cast<const Building*>(new_cell);
        if (!building_cell) return; // it is not a Building

        display_coeff = false;
        calculateOnBuildResources(const_cast<Building*>(building_cell));

        informResourceBar();
        updateCoeffDisplays();
    }

    void onNewCitizenArrival(long int citizen_cnt)
    {
        display_coeff = false;
        long int start_citizen_cnt = citizen_cnt;
        onNewCitizen(citizen_cnt);

        user_res.free_population -= (start_citizen_cnt - citizen_cnt);

        informResourceBar();
        updateCoeffDisplays();
    }

    void onCitizenLeave(long int citizen_cnt)
    {
        long int start_citizen = citizen_cnt;
        killCitizen(citizen_cnt);

        user_res.free_population += (start_citizen - citizen_cnt);

        informResourceBar();
        updateCoeffDisplays();
    }

    void onDelete(const Cell* delete_cell)
    {
        const Building* building_cell = dynamic_cast<const Building*>(delete_cell);
        if (!building_cell) return; // it is not a Building

        calculateOnDeleteResources(building_cell);

        informResourceBar();
        updateCoeffDisplays();
    }

    Resources getUserRes() const
    {
        return user_res;
    }

    static bool hasLost()
    {
        return (current_manager != nullptr) && current_manager->getUserRes() < kZeroResources;
    }

    bool tryBuild(FieldType building_type)
    {
        return (CellKeeper::getAppearIncome(building_type).wood  * -1) <= user_res.wood &&
               (CellKeeper::getAppearIncome(building_type).stone * -1) <= user_res.stone;
    }

    ~ResourceManager()
    {
        current_manager = nullptr;
    }

    void setCellInterlayer(CellInterlayerI* _cell_interlayer)
    {
        cell_interlayer = _cell_interlayer;
    }

    void onCellViewDeleted()
    {
        display_coeff = true;
    }

private:

    void updateCoeffDisplays()
    {
        if (!display_coeff) return;

        for (auto building : buildings)
        {
            CoeffChangedEvent* coeff_changed_event = new CoeffChangedEvent(building.ptr->getIndex(), building.ptr->getCurWorkers(), building.max_workers);
            cell_interlayer->pushToView(coeff_changed_event);
        }
    }

    void informResourceBar()
    {
        resource_bar_interlayer.pushToView(new ResourceEvent(user_res));
    }

    void calculateOnBuildResources(Building* building_cell)
    {
        Resources appear_res = building_cell->getAppearIncome();
        user_res += appear_res;

        long int cur_workers = 0, max_workers = 0;
        Resources building_tick_income = calculateBuildTickResources(building_cell, building_cell->getTickIncome(), cur_workers, max_workers);

        tryAddHouse(building_cell, appear_res.population, building_tick_income, cur_workers, max_workers);
        buildings.emplace_back(building_cell, building_tick_income, cur_workers, max_workers);
    }

    Resources calculateBuildTickResources(Building* building_cell, Resources default_tick, long int& cur_workers, long int& max_workers)
    {
        max_workers = building_cell->getMaxWorkers();
        if (max_workers == 0) 
        {
            tick_income += default_tick;
            return default_tick; 
        }

        long available_workers = user_res.free_population;
        cur_workers       = std::min(available_workers, building_cell->getMaxWorkers());

        user_res.free_population -= cur_workers;
        building_cell->setCurWorkers(cur_workers);

        double effectiveness_coeff     = static_cast<double>(cur_workers) / static_cast<double>(max_workers);
        Resources building_tick_income = default_tick * effectiveness_coeff;

        tick_income += building_tick_income;

        return building_tick_income;
    }

    void tryAddHouse(Building* building, long int citizen, Resources default_tick, long int& cur_workers, long int& max_workers)
    {
        if (building->getFieldType() == static_cast<size_t>(ReservedTypes::HOUSE))
        {
            houses.emplace_back(building, default_tick, citizen, citizen, default_tick);
            (houses.end() - 1)->ptr->setCurWorkers(citizen);

            cur_workers = max_workers = citizen;
        }
    }

    void calculateOnDeleteResources(const Building* delete_building)
    {
        Resources destroy_res = delete_building->getDestroyIncome();
        user_res += destroy_res;

        auto building_it = findBuildingByPtr(delete_building);

        tick_income -= building_it->tick_income;

        long int free_pop = delete_building->getCurWorkers();
        if (free_pop > 0 && delete_building->getMaxWorkers() > 0)
        {
            user_res.free_population += free_pop;
            onNewCitizen(free_pop);
        }

        buildings.erase(building_it);
        tryDeleteHouse(delete_building);
    }

    void tryDeleteHouse(const Building* delete_building)
    {
        if (delete_building->getFieldType() == static_cast<size_t>(ReservedTypes::HOUSE))
        {
                  auto it     = houses.begin();
            const auto end_it = houses.end();

            for (; it != end_it; ++it)
            {
                if (it->ptr == delete_building)
                {
                    houses.erase(it);
                    break;
                }
            }
        }
    }

    void onNewCitizen(long int& citizen_cnt)
    {
        for (auto& building : buildings)
        {
            recalcNewCitizenResources(building, citizen_cnt);
            if (citizen_cnt == 0) break;
        }
    }

    void recalcNewCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        long int max_workers = building.ptr->getMaxWorkers();
        if (max_workers == 0) return;

        long int cur_workers = building.ptr->getCurWorkers();
        long int new_workers = std::min(available_pop, max_workers - cur_workers);
        if (new_workers == 0) return;
        
        available_pop -= new_workers;
        cur_workers   += new_workers;
        building.ptr->setCurWorkers(cur_workers);

        tick_income -= building.tick_income;

        double effectiveness_coeff = static_cast<double>(cur_workers) / static_cast<double>(max_workers);
        building.tick_income = building.ptr->getTickIncome() * effectiveness_coeff;
        building.cur_workers = cur_workers;

        tick_income += building.tick_income;
    }

    void killCitizen(long int& citizen_cnt)
    {
        for (auto& building : buildings)
        {
            recalcLeaveCitizenResources(building, citizen_cnt);
            if (citizen_cnt == 0) break;
        }
    }

    void recalcLeaveCitizenResources(BuildingProperties& building, long int& available_pop)
    {
        long int max_workers = building.ptr->getMaxWorkers();
        if (max_workers == 0) return;

        long int cur_workers    = building.ptr->getCurWorkers();
        long int killed_workers = std::min(available_pop, cur_workers);
        if (killed_workers == 0) return;

        available_pop -= killed_workers;
        cur_workers   -= killed_workers;
        building.ptr->setCurWorkers(cur_workers);

        tick_income -= building.tick_income;

        double effectiveness_coeff = static_cast<double>(cur_workers) / static_cast<double>(max_workers);
        building.tick_income = building.ptr->getTickIncome() * effectiveness_coeff;
        building.cur_workers = cur_workers;

        tick_income += building.tick_income;
    }

    void recalculateHouseIncome(HouseProperties& house)
    {
        tick_income -= house.tick_income;

        double effectiveness_coeff = static_cast<double>(house.ptr->getCurWorkers()) / static_cast<double>(house.max_workers);
        house.tick_income  = house.default_tick_income * effectiveness_coeff;

        tick_income += house.tick_income;
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
    CellInterlayerI*       cell_interlayer;

    // "Resources" parameter needed to save resources 
    // that are needed for building
    // default: Resources()
    std::vector<BuildingProperties> buildings;
    std::vector<HouseProperties>    houses;

    bool display_coeff = true;
};