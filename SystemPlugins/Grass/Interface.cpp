#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType GrassInterface::getType() 
{
    return CellType::CELL;
}

Cell* GrassInterface::createCell() 
{
    return new GrassCell();
}

CellView* GrassInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new GrassView(pos, cell_view_group);
}

Bitmask GrassInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources GrassInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t GrassInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::GRASS);
}

const char* GrassInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new GrassInterface();
}