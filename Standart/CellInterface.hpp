#pragma once

#include "GameLogic/Building.hpp"
#include "GameLogic/Cell.hpp"
#include "Utils/Bitmask.hpp"
#include "GameLogic/Resources.hpp"

enum GameObjectType
{
    CELL,
    BUILDING
};

struct CellInterface
{
    GameObjectType getType        ();
    Cell*          createCell     (const FieldType field_type);
    Building*      createBuilding (const size_t _field_type, const long int _max_workers = 0);
    Bitmask        getBuildMask   ();
    Resources      getAppearIncome();
};