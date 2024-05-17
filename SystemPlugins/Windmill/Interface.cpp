#include "Cell.hpp"

#include "Interface.hpp"

CellType WindmillInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WindmillInterface::createCell() 
{
    return new WindmillCell();
}

Bitmask WindmillInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources WindmillInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t WindmillInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::WINDMILL);
}

const char* WindmillInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new WindmillInterface();
}