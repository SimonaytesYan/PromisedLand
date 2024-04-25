#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType WindmillInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WindmillInterface::createCell() 
{
    return new WindmillCell();
}

CellView* WindmillInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new WindmillView(pos, cell_view_group);
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