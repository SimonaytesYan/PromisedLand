#pragma once

#include "GameLogic/Building.hpp"
#include "GameLogic/Cell.hpp"
#include "Utils/Bitmask.hpp"
#include "GameLogic/Resources.hpp"

class CellView;
class CellViewGroup;

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
    MINE,
    WASTELAND,
    OVEN,
    WATER_TOWER
};

struct CellInterface
{
    virtual CellType       getType        () = 0;
    virtual Cell*          createCell     () = 0;
    virtual Bitmask        getBuildMask   () = 0;
    virtual Resources      getAppearIncome() = 0;
    virtual size_t         getId          () = 0;
    virtual const char*    getAsset       () = 0;

    virtual ~CellInterface() = default;
};