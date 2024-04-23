#pragma once

#include "GameLogic/Building.hpp"
#include "GameLogic/Cell.hpp"
#include "Graphics/CellView/CellView.hpp"
#include "Utils/Bitmask.hpp"
#include "Utils/GraphicPrimitives.hpp"
#include "GameLogic/Resources.hpp"

enum class CellType
{
    CELL,
    BUILDING,
    ERROR
};

enum class ReservedTypes
{
    // CELLS
    GRASS,
    WATER,
    FOREST,
    ISLAND,

    // BUILDINGS
    HOUSE,
    SAWMILL,
    WELL,
    WINDMILL,
    MINE
};

struct CellInterface
{
    virtual CellType       getType        ()                                                = 0;
    virtual Cell*          createCell     (const FieldType field_type)                      = 0;
    virtual CellView*      createCellView (const Point pos, CellViewGroup& cell_view_group) = 0;
    virtual Bitmask        getBuildMask   ()                                                = 0;
    virtual Resources      getAppearIncome()                                                = 0;
    virtual size_t         getId          ()                                                = 0;
};