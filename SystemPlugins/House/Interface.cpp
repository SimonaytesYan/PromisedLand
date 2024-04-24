#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType HouseInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* HouseInterface::createCell() 
{
    return new HouseCell();
}

CellView* HouseInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new HouseView(pos, cell_view_group);
}

Bitmask HouseInterface::getBuildMask() 
{
    return ~((1 << 1) | (1 << 2) | (1 << 3));
}

Resources HouseInterface::getAppearIncome() 
{
    return Resources(0,  0, -15, 5,  5, 0);
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