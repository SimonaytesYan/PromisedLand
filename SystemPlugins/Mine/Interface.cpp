#include "Cell.hpp"

#include "Interface.hpp"

CellType MineInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* MineInterface::createCell() 
{
    return new MineCell();
}

Bitmask MineInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources MineInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t MineInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::MINE);
}

const char* MineInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new MineInterface();
}