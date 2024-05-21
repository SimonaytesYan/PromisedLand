#include "Cell.hpp"

#include "Interface.hpp"

CellType WaterTowerInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WaterTowerInterface::createCell() 
{
    return new WaterTowerCell();
}

Bitmask WaterTowerInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources WaterTowerInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t WaterTowerInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::WATER_TOWER);
}

const char* WaterTowerInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new WaterTowerInterface();
}