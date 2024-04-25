#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType WastelandInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* WastelandInterface::createCell() 
{
    return new WastelandCell();
}

CellView* WastelandInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new WastelandView(pos, cell_view_group);
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