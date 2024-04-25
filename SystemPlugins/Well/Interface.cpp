#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType WellInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WellInterface::createCell() 
{
    return new WellCell();
}

CellView* WellInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new WellView(pos, cell_view_group);
}

Bitmask WellInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources WellInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t WellInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::WELL);
}

const char* WellInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new WellInterface();
}