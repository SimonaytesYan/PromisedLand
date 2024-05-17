#include "Cell.hpp"

#include "Interface.hpp"

CellType WaterInterface::getType() 
{
    return CellType::CELL;
}

Cell* WaterInterface::createCell() 
{
    return new WaterCell();
}

Bitmask WaterInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources WaterInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t WaterInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::WATER);
}

const char* WaterInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new WaterInterface();
}