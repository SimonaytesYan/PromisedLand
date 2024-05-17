#include "Cell.hpp"
#include "Interface.hpp"

CellType ForestInterface::getType() 
{
    return CellType::CELL;
}

Cell* ForestInterface::createCell() 
{
    return new ForestCell();
}

Bitmask ForestInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources ForestInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t ForestInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::FOREST);
}

const char* ForestInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new ForestInterface();
}