#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType WellInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WellInterface::createCell() 
{
    return new SawmillCell();
}

CellView* WellInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new SawmillView(pos, cell_view_group);
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
    return static_cast<size_t>(ReservedTypes::SAWMILL);
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