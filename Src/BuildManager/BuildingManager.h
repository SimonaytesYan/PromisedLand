#pragma once
#include "Field/Building/Building.h"

class BuildingManager
{
public:

    BuildingManager() :
    current (nullptr)
    {}

    void setBuildingType(Building* building)
    {
        current = building;
    }

    Building* getBuildingType()
    { return current; }

    bool buildingTypeSetted()
    { return current == nullptr; }

private:
    Building* current;
};