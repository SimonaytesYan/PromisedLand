#include "Cell.hpp"

#include "Interface.hpp"

CellType OvenInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* OvenInterface::createCell() 
{
    return new OvenCell();
}

Bitmask OvenInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources OvenInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t OvenInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::OVEN);
}

const char* OvenInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new OvenInterface();
}