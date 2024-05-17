#include "Cell.hpp"

#include "Interface.hpp"

CellType GrassInterface::getType() 
{
    return CellType::CELL;
}

Cell* GrassInterface::createCell() 
{
    return new GrassCell();
}

Bitmask GrassInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources GrassInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t GrassInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::GRASS);
}

const char* GrassInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new GrassInterface();
}