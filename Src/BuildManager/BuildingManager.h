#pragma once
#include "Field/Building/Building.h"

class BuildingManager
{
public:
    void setBuildingType(Building* building);
    Building* getBuildingType();

private:
    Building* current;
};