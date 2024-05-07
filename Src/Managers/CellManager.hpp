#pragma once

#include <vector>

#include "../GameLogic/Tiles/Cell.hpp"
#include "ResourceManager.hpp"
#include "../Utils/Utils.hpp"

class CellInterlayer;

class CellManager
{
    friend CellInterlayer;

public:
    explicit CellManager(CellInterlayer* _cell_interlayer)
      : cells           (),
        res_manager     (nullptr),
        cell_interlayer (_cell_interlayer),
        cell_type       () 
    {}

    explicit CellManager(ResourceManager* _res_manager = nullptr, CellInterlayer* _cell_interlayer = nullptr)
      : cells           (),
        res_manager     (_res_manager),
        cell_interlayer (_cell_interlayer),
        cell_type       () 
    {}

    // Non-copyable
    CellManager(const CellManager& other)           = delete;
    CellManager operator=(const CellManager& other) = delete;

    // Non-movable
    CellManager(CellManager&& other)           = delete;
    CellManager operator=(CellManager&& other) = delete;

    ~CellManager()
    {
        for (size_t i = 0; i < cells.size(); ++i)
        { delete cells[i]; }
    }

    void setResourceManager(ResourceManager* _res_manager)
    { res_manager = _res_manager; }

    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    { cell_interlayer = _cell_interlayer; }

    void setCellType(const FieldType _cell_type)
    { cell_type = _cell_type; }

    void onTick()
    {
        res_manager->onTick();
    }

    void onNewCitizenArrival(const long int citizen_cnt)
    {
        res_manager->onNewCitizenArrival(citizen_cnt);
    }

    void deleteCell(const size_t index)
    {
        if (cells[index]->getFieldType() == static_cast<size_t>(ReservedTypes::HOUSE))
        {
            Building* house = static_cast<Building*>(cells[index]);
            res_manager->onCitizenLeave(house->getDestroyIncome().population * -1);
        }

        res_manager->onDelete(cells[index]);

        delete cells[index];
        cells.erase(cells.begin() + index);
    }

private:
    void tryBuildCell(const size_t index, const Point position);
    void createCell(const Point position);
    void createCell(Cell* new_cell)
    { 
        cells.push_back(new_cell); 
        new_cell->setIndexInCellGroup(cells.size() - 1);
    }

private:
    std::vector<Cell*> cells;
    ResourceManager*   res_manager;
    CellInterlayer*    cell_interlayer;
    FieldType          cell_type;
};
