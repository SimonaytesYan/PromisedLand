#pragma once

#include <vector>

#include "../GameLogic/Tiles/Building.hpp"
#include "../GameLogic/Tiles/Cell.hpp"
#include "../GameLogic/CellInterface.hpp"

class CellKeeper
{
public:
    static void add(CellInterface* _new_interface)
    {
        unique_cells.push_back(_new_interface);
    }

    static Cell* createCell(const FieldType field_type)
    {
        return unique_cells[field_type]->createCell(field_type);
    } 

    static Building* createBuilding(const FieldType field_type, const long int max_workers = 0)
    {
        return unique_cells[field_type]->createBuilding(field_type, max_workers);
    } 

    static Bitmask getBuildMask(const FieldType field_type)
    {
        return unique_cells[field_type]->getBuildMask();
    }

    static Resources getAppearIncome(const FieldType field_type)
    {
        return unique_cells[field_type]->getAppearIncome();
    }

private:
    static std::vector<CellInterface*> unique_cells;
};