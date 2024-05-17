#include "Cell.hpp"

#include "Interface.hpp"

CellType HouseInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* HouseInterface::createCell() 
{
    return new HouseCell();
}

Bitmask HouseInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources HouseInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t HouseInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::HOUSE);
}

const char* HouseInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new HouseInterface();
}