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

    static CellType getType(const FieldType field_type)
    {
        return unique_cells[findByInterfaceId(field_type)]->getType();
    }

    static Cell* createCell(const FieldType field_type)
    {
        return unique_cells[findByInterfaceId(field_type)]->createCell(field_type);
    } 

    static CellView* createCellView(const FieldType field_type, const Point pos, CellViewGroup& cell_view_group)
    {
        return unique_cells[findByInterfaceId(field_type)]->createCellView(pos, cell_view_group);
    } 

    static Bitmask getBuildMask(const FieldType field_type)
    {
        return unique_cells[findByInterfaceId(field_type)]->getBuildMask();
    }

    static Resources getAppearIncome(const FieldType field_type)
    {
        return unique_cells[findByInterfaceId(field_type)]->getAppearIncome();
    }

private:

    static long findByInterfaceId(const size_t field_type)
    {
        const size_t interface_cnt = unique_cells.size();
        for (size_t i = 0; i < interface_cnt; ++i)
        {
            if (unique_cells[i]->getId() == field_type)
            {
                return i;
            }
        }

        return -1;
    }

private:
    static std::vector<CellInterface*> unique_cells;
};