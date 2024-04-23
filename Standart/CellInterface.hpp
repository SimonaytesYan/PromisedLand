#pragma once

#include "GameLogic/Building.hpp"
#include "GameLogic/Cell.hpp"
#include "Graphics/CellView/CellView.hpp"
#include "Utils/Bitmask.hpp"
#include "GameLogic/Resources.hpp"

enum GameObjectType
{
    CELL,
    BUILDING
};

struct CellInterface
{
    virtual GameObjectType getType        () = 0;
    virtual Cell*          createCell     (const FieldType field_type) = 0;
    virtual CellView*      createCellView () = 0;
    virtual Bitmask        getBuildMask   () = 0;
    virtual Resources      getAppearIncome() = 0;
};