#include "Cell.hpp"
#include "Interface.hpp"

CellType WastelandInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WastelandInterface::createCell() 
{
    return new WastelandCell();
}

Bitmask WastelandInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources WastelandInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t WastelandInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::WASTELAND);
}

const char* WastelandInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new WastelandInterface();
}